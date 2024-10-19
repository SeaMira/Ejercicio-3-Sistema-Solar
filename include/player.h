#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreCameraMan.h"

class SolarSystemPlayer :  public OgreBites::InputListener {
public:
    SolarSystemPlayer(Ogre::SceneNode* camNode, Ogre::Camera* cam, Ogre::Vector3& lookAt, Ogre::Vector3& lookUp, float yaw, float pitch);
    virtual ~SolarSystemPlayer() {}

    void frameRendered(const Ogre::FrameEvent& evt);

    bool keyPressed(const OgreBites::KeyboardEvent& evt);

    bool keyReleased(const OgreBites::KeyboardEvent& evt);
    
    bool mouseMoved(const OgreBites::MouseMotionEvent& evt);

    // for joystick
    bool axisMoved(const OgreBites::AxisEvent& evt);

    bool buttonPressed(const OgreBites::ButtonEvent& evt);

    bool buttonReleased(const OgreBites::ButtonEvent& evt);

    void setLookAt();
private:
    Ogre::SceneNode* mNode;
    Ogre::Camera* mCam;
    Ogre::Vector3 mPos;
    Ogre::Vector3 mLookAt;
    Ogre::Vector3 mLookUp;
    Ogre::Vector3 mInitUp;
    float mYaw, mPitch;
    float mSpeed = 10.0f;

    // mouse
    bool firstMouse = true;
    float mLastX = 0.0f, mLastY = 0.0f;
    float MARGIN = 10.0f;
    float mSensitivity = 0.1f;
    float EDGE_STEP = 10.0f;

    bool OnUpperEdge = false, OnLowerEdge = false, OnRightEdge = false, OnLeftEdge = false;
    bool key_up = false, key_down = false, key_right = false, key_left = false, key_space = false, key_lshift = false;

    // for gamepad
    float mLValueX = 0.0f, mLValueY = 0.0f, mRValueX = 0.0f, mRValueY = 0.0f;
    bool button_x = false, button_circle = false;
};