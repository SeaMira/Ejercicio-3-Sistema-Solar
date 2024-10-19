#pragma once

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include <vector>


class SolarSystemPlanet : public Ogre::FrameListener {
public:
    // Constructor para planetas con posici�n fija (sin padre)
    SolarSystemPlanet(Ogre::SceneManager* sceneManager, const std::string& name,
        const Ogre::Vector3& position, float scale, const std::string& meshName);

    // Constructor para planetas que orbitan alrededor de un padre
    SolarSystemPlanet(Ogre::SceneManager* sceneManager, const std::string& name,
        SolarSystemPlanet* parent, float orbitRadius, float scale, float speed, const std::string& meshName);

    // Actualiza la posici�n del planeta (llamar en cada frame)
    bool frameStarted(const Ogre::FrameEvent& evt);
    void update(const float dt);

    // Agrega un planeta hijo
    void addChild(SolarSystemPlanet* child);

private:
    Ogre::SceneNode* mNode;          // Nodo de OGRE para posicionar el planeta
    Ogre::Entity* mEntity;           // Entidad de OGRE para la apariencia del planeta
    SolarSystemPlanet* mParent;                 // Planeta padre (si es nullptr, tiene posici�n fija)
    float mOrbitRadius;              // Radio de la �rbita alrededor del padre
    float mScale;                    // Escala del planeta
    float mOrbitAngle;               // �ngulo de la �rbita (se incrementa con el tiempo)
    float mSpeed;
    std::vector<SolarSystemPlanet*> mChildren;  // Planetas hijos que orbitan alrededor de este planeta
};