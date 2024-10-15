#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "planet.h"

class SolarSystem : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    SolarSystem();
    virtual ~SolarSystem() {}

    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

SolarSystem::SolarSystem() : OgreBites::ApplicationContext("SolarSystem")
{
}

void SolarSystem::setup()
{
    // Calling the base first, adding the input listener
    OgreBites::ApplicationContext::setup();
    addInputListener(this);

    // Pointer to the default root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();

    // Registering the scene with the RTShaderSystem
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // A light source is needed
    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);

    // Setting up the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);
    cam->setAutoAspectRatio(false);
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 40);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    camNode->attachObject(cam);

    // Setting up the viewport
    getRenderWindow()->addViewport(cam);

    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("assets", "FileSystem");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool SolarSystem::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}

int main(int argc, char **argv)
{
    try
    {
        SolarSystem app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (Ogre::Exception& e)
    {
        Ogre::LogManager::getSingleton().logMessage(e.what());
    }
    return 0;
}