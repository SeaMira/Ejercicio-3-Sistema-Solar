#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"

class SolarSystemPlayer :  public OgreBites::InputListener {
public:
    SolarSystemPlayer(Ogre::SceneNode* playerNode, Ogre::SceneNode* camNode, Ogre::Vector3& initPos, Ogre::Vector3& initLookAt) {}
    virtual ~SolarSystemPlayer() {}
    void checkMove(float deltax, float deltay, float dt);
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
    Ogre::SceneNode* mNode;
    Ogre::SceneNode* mCamNode;
    Ogre::Vector3 mPos;
    Ogre::Vector3 mLookAt;
    float mMaxCounter, mCounter = 0.0f;
};

