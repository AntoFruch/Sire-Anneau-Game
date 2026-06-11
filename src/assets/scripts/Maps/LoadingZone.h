//
// Created by Antonin Fruchet on 10/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_LOADINGZONE_H
#define COMPONENT_BASED_ARCH_LOADINGZONE_H


#include "Engine.h"

class LoadingZone : public Component
{
    const std::string sceneToLoad;
    const unsigned int doorId;
    const unsigned int targetDoorId;

    sf::Vector2f spawnPoint;

public:
    LoadingZone(const std::string& sceneToLoad, unsigned int doorId, unsigned int targetDoorId, float spawnX, float spawnY);
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    unsigned int getDoorID();
    const sf::Vector2f& getSpawnPoint() const;
};


#endif //COMPONENT_BASED_ARCH_LOADINGZONE_H
