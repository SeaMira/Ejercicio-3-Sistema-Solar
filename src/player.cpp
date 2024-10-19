#include "player.h"
#include "OgreMath.h"
#include <iostream>
#include <algorithm>

SolarSystemPlayer::SolarSystemPlayer(Ogre::SceneNode* camNode, Ogre::Camera* cam, Ogre::Vector3& lookAt, Ogre::Vector3& lookUp, float yaw, float pitch) :
			mCam(cam), mNode(camNode), mLookAt(lookAt), mLookUp(lookUp), mYaw(yaw), mPitch(pitch) {
	mPos = camNode->getPosition();
	camNode->yaw(Ogre::Degree(yaw));
	camNode->pitch(Ogre::Degree(pitch));
	int SCR_WIDTH = mCam->getViewport()->getActualWidth();
	int SCR_HEIGHT = mCam->getViewport()->getActualHeight();
	this->mLastX = (float)SCR_WIDTH / 2.0f;
	this->mLastY = (float)SCR_HEIGHT / 2.0f;
	mInitUp = lookUp;

}


bool SolarSystemPlayer::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == OgreBites::SDLK_LEFT) key_left = true;

	if (evt.keysym.sym == OgreBites::SDLK_RIGHT) key_right = true;
	if (evt.keysym.sym == OgreBites::SDLK_UP) key_up = true;
	if (evt.keysym.sym == OgreBites::SDLK_DOWN) key_down = true;
	if (evt.keysym.sym == OgreBites::SDLK_SPACE) key_space = true;
	if (evt.keysym.sym == OgreBites::SDLK_LSHIFT) key_lshift = true;

	return true;
}

bool SolarSystemPlayer::keyReleased(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == OgreBites::SDLK_LEFT) key_left = false;
	if (evt.keysym.sym == OgreBites::SDLK_RIGHT) key_right = false;
	if (evt.keysym.sym == OgreBites::SDLK_UP) key_up = false;
	if (evt.keysym.sym == OgreBites::SDLK_DOWN) key_down = false;
	if (evt.keysym.sym == OgreBites::SDLK_SPACE) key_space = false;
	if (evt.keysym.sym == OgreBites::SDLK_LSHIFT) key_lshift = false;

	return true;
}

bool SolarSystemPlayer::buttonPressed(const OgreBites::ButtonEvent& evt) {
	
	if (evt.button == 0) {
		std::cout << "X Button Pressed" << std::endl;
		button_x = true;
	}
		
	if (evt.button == 1) {
		std::cout << "Circle Button Pressed" << std::endl;
		button_circle = true;
	}
	if (evt.button == 2) std::cout << "Square Button Pressed" << std::endl; 
	if (evt.button == 3) std::cout << "Triangle Button Pressed" << std::endl;
	
	return true;
}


bool SolarSystemPlayer::buttonReleased(const OgreBites::ButtonEvent& evt) {
	if (evt.button == 0) {
		std::cout << "X Button Released" << std::endl;
		button_x = false;
	}

	if (evt.button == 1) {
		std::cout << "Circle Button Released" << std::endl;
		button_circle = false;
	}
	if (evt.button == 2) std::cout << "Square Button Released" << std::endl;
	if (evt.button == 3) std::cout << "Triangle Button Released" << std::endl;

	return true;
}


void SolarSystemPlayer::setLookAt() {
	mPitch = std::clamp(mPitch, -89.0f, 89.0f);
	Ogre::Vector3 lookAt;
	// Crear quaternions para las rotaciones en yaw y pitch
	Ogre::Quaternion qYaw(Ogre::Degree(mYaw), Ogre::Vector3::UNIT_Y); // Rotación alrededor del eje Y
	Ogre::Quaternion qPitch(Ogre::Degree(mPitch), Ogre::Vector3::UNIT_X); // Rotación alrededor del eje X

	// Combinar las rotaciones y aplicar la orientación a la cámara
	mNode->setOrientation(qYaw * qPitch);
	lookAt = mNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	lookAt.normalise();
	mLookAt = lookAt;
}


bool SolarSystemPlayer::mouseMoved(const OgreBites::MouseMotionEvent& evt) {
	float sensitivity = 0.1f; // Ajustar según la sensibilidad deseada
	mYaw -= evt.xrel * sensitivity;   // Movimiento del mouse en X ajusta el yaw
	mPitch -= evt.yrel * sensitivity; // Movimiento del mouse en Y ajusta el pitch


	int SCR_WIDTH = mCam->getViewport()->getActualWidth();
	int SCR_HEIGHT = mCam->getViewport()->getActualHeight();

	if (evt.x <= MARGIN) {
        OnLeftEdge = true;
        OnRightEdge = false;
    }
    else if (evt.x >= (SCR_WIDTH - MARGIN)) {
        OnLeftEdge = false;
        OnRightEdge = true;
    }
    else {
        OnLeftEdge = false;
        OnRightEdge = false;
    }

    if (evt.y <= MARGIN) {
        OnUpperEdge = true;
        OnLowerEdge = false;
    }
    else if (evt.y >= (SCR_HEIGHT - MARGIN)) {
        OnUpperEdge = false;
        OnLowerEdge = true;
    }
    else {
        OnUpperEdge = false;
        OnLowerEdge = false;
    }

	setLookAt();
	return true;
}


bool SolarSystemPlayer::axisMoved(const OgreBites::AxisEvent& evt) {
	float x = (float)(evt.value) / 32767.0f;
	float deadZone = 0.1;
	if (std::abs(x) < deadZone) {
		x = 0.0f; // Si el valor está dentro de la zona muerta, se considera como cero.
	}

	switch (evt.axis) {
	case 0:
		mLValueX = x;
		break;
	case 1:
		mLValueY = x;
		break;
	case 2:
		mRValueX = x;
		break;
	case 3:
		mRValueY = x;
		break;
	default:
		break;
	}

	setLookAt();
	return true;
}

void SolarSystemPlayer::frameRendered(const Ogre::FrameEvent& evt) {
	float dt = evt.timeSinceLastFrame;
	if (key_left) {
		mPos = mNode->_getDerivedPosition() - mCam->getRealRight() * mSpeed * dt;
		mNode->_setDerivedPosition(mPos);
	}
	else if (mLValueX < 0.0f) {
		mPos = mNode->_getDerivedPosition() + mCam->getRealRight() * mSpeed * dt * mLValueX;
		mNode->_setDerivedPosition(mPos);
	}

	if (key_right) {
		mPos = mNode->_getDerivedPosition() + mCam->getRealRight() * mSpeed * dt;
		mNode->_setDerivedPosition(mPos);
	}
	else if (mLValueX > 0.0f) {
		mPos = mNode->_getDerivedPosition() + mCam->getRealRight() * mSpeed * dt * mLValueX;
		mNode->_setDerivedPosition(mPos);
	}

	if (key_up) {
		mPos = mNode->_getDerivedPosition() + mLookAt * mSpeed * dt;
		mNode->_setDerivedPosition(mPos);
	}
	else if (mLValueY > 0.0f) {
		mPos = mNode->_getDerivedPosition() - mLookAt * mSpeed * dt * mLValueY;
		mNode->_setDerivedPosition(mPos);
	}

	if (key_down) {
		mPos = mNode->_getDerivedPosition() - mLookAt * mSpeed * dt;
		mNode->_setDerivedPosition(mPos);
	}
	else if (mLValueY < 0.0f) {
		mPos = mNode->_getDerivedPosition() - mLookAt * mSpeed * dt * mLValueY;
		mNode->_setDerivedPosition(mPos);
	}

	if (key_space || button_x) {
		mPos = mNode->_getDerivedPosition() + mInitUp * mSpeed * dt;
		mNode->_setDerivedPosition(mPos);
	}
	if (key_lshift || button_circle) {
		mPos = mNode->_getDerivedPosition() - mInitUp * mSpeed * dt;
		mNode->_setDerivedPosition(mPos);
	}


	mYaw -= mRValueX;
	mPitch -= mRValueY;
	

	// mouse

	if (OnLeftEdge) {
		mYaw += EDGE_STEP * dt * mSpeed;
	}
	else if (OnRightEdge) {
		mYaw -= EDGE_STEP * dt * mSpeed;
	}

	if (OnUpperEdge) {
		if (mPitch < 90.0f) {
			mPitch += EDGE_STEP * dt * mSpeed;
		}
	}
	else if (OnLowerEdge) {
		if (mPitch > -90.0f) {
			mPitch -= EDGE_STEP * dt * mSpeed;
		}
	}

	 setLookAt();
}