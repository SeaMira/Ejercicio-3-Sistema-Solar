#include "planet.h"

SolarSystemPlanet::SolarSystemPlanet(Ogre::SceneManager* sceneManager, const std::string& name,
    const Ogre::Vector3& position, float scale, const std::string& meshName)
    : mParent(nullptr), mOrbitRadius(0), mScale(scale), mOrbitAngle(0), mSpeed(1.0f) {
    mNode = sceneManager->getRootSceneNode()->createChildSceneNode(name);
    
    mNode->setInheritScale(false);
    mNode->setScale(Ogre::Vector3(scale));
    mNode->setPosition(position);

    mEntity = sceneManager->createEntity(name, meshName); // Usa un modelo de esfera
    mNode->attachObject(mEntity);
}

SolarSystemPlanet::SolarSystemPlanet(Ogre::SceneManager* sceneManager, const std::string& name,
    SolarSystemPlanet* parent, float orbitRadius, float scale, float speed, const std::string& meshName)
    : mParent(parent), mOrbitRadius(orbitRadius), mScale(scale), mOrbitAngle(0), mSpeed(speed) {
    mNode = parent->mNode->createChildSceneNode(name);
    mNode->setInheritScale(false);
    mNode->setScale(Ogre::Vector3(scale));

    mEntity = sceneManager->createEntity(name, meshName); // Usa un modelo de esfera
    mNode->attachObject(mEntity);
}

bool SolarSystemPlanet::frameStarted(const Ogre::FrameEvent& evt) {
    if (mParent) {
        // Incrementar el ángulo de la órbita (ajustar la velocidad según sea necesario)
        mOrbitAngle += evt.timeSinceLastFrame * 0.1f * mSpeed;

        // Calcular la nueva posición en la órbita usando el ángulo
        float x = mParent->mNode->getPosition().x + mOrbitRadius * Ogre::Math::Cos(mOrbitAngle);
        float z = mParent->mNode->getPosition().z + mOrbitRadius * Ogre::Math::Sin(mOrbitAngle);
        mNode->setPosition(x, mNode->getPosition().y, z);
    }

    // Actualizar la posición de los hijos
    for (SolarSystemPlanet* child : mChildren) {
        child->update(evt.timeSinceLastFrame);
    }
    return true;
}

void SolarSystemPlanet::update(const float dt) {
    
    // Incrementar el ángulo de la órbita (ajustar la velocidad según sea necesario)
    mOrbitAngle += dt * 0.1f * mSpeed;

    // Calcular la nueva posición en la órbita usando el ángulo
    float x = mOrbitRadius * Ogre::Math::Cos(mOrbitAngle);
    float z = mOrbitRadius * Ogre::Math::Sin(mOrbitAngle);
    mNode->setPosition(x, mNode->getPosition().y, z);
    

    // Actualizar la posición de los hijos
    for (SolarSystemPlanet* child : mChildren) {
        child->update(dt);
    }
}

void SolarSystemPlanet::addChild(SolarSystemPlanet* child) {
    mChildren.push_back(child);
}