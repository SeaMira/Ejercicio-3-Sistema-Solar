#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "planet.h"
#include "player.h"

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
    light->setType(Ogre::Light::LT_POINT);
    light->setAttenuation(1000.0f, 0.5f, 0.0f, 0.0f);

    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 30, 0);
    lightNode->attachObject(light);

    Ogre::Light* light2 = scnMgr->createLight("MainLight2");
    light2->setType(Ogre::Light::LT_POINT);
    light2->setAttenuation(1000.0f, 0.5f, 0.0f, 0.0f);

    Ogre::SceneNode* lightNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode2->setPosition(0, -30, 0);
    lightNode2->attachObject(light2);

    // Setting up the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);
    cam->setAutoAspectRatio(false);
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 200);
    Ogre::Vector3 initLookAt = Ogre::Vector3::NEGATIVE_UNIT_Z;
    Ogre::Vector3 initLookUp = Ogre::Vector3::UNIT_Y;
    camNode->setDirection(initLookAt, Ogre::Node::TS_WORLD, initLookUp);
    // Obtener la orientación actual de la cámara como un quaternion
    Ogre::Quaternion orientation = camNode->getOrientation();
    // Convertir el quaternion a *yaw* y *pitch*
    float yaw = 0.0f;
    float pitch = 0.0f;

    camNode->attachObject(cam);

    // Setting up the viewport
    Ogre::RenderWindow* renderWindow = getRenderWindow();
    renderWindow->addViewport(cam);

    SolarSystemPlayer* player = new SolarSystemPlayer(camNode, cam, initLookAt, initLookUp, yaw, pitch);

    addInputListener(player);

    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("assets", "FileSystem");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    /*Ogre::Entity* sphereEntity = scnMgr->createEntity("Sphere", "ball.obj");
    Ogre::SceneNode* sphereNode = scnMgr->getRootSceneNode()->createChildSceneNode("SphereNode");
    sphereNode->setPosition(0.0f, 0.0f, 0.0f);
    sphereNode->yaw(Ogre::Degree(90));
    sphereNode->attachObject(sphereEntity);*/

    // Crear un planeta con posición fija (sin padre)
    SolarSystemPlanet* sun = new SolarSystemPlanet(scnMgr, "Sun", Ogre::Vector3(0, 0, 0), 0.1f, "13913_Sun_v2_l3.obj");

    // Crear un planeta que orbita alrededor del sol
    SolarSystemPlanet* earth = new SolarSystemPlanet(scnMgr, "Earth", sun, 2000.0f, 1.0f, 0.5f, "MarsPlanet.obj");

    // Crear una luna que orbita alrededor de la Tierra
    SolarSystemPlanet* moon = new SolarSystemPlanet(scnMgr, "Moon", earth, 45.0f, 1.0f, 5.0f, "Moon 2K.obj");

    // Agregar tierra como hijo del sol
    sun->addChild(earth);
    
    // Agregar la luna como hijo de la Tierra
    earth->addChild(moon);

    root->addFrameListener(sun);

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