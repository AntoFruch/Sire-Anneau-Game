//
// Created by Antonin Fruchet on 10/06/2026.
//

#include "LoadingZone.h"

#include "LoadingZoneManager.h"
#include "scripts/entities/PlayerController.h"

LoadingZone::LoadingZone(const std::string& sceneToLoad, unsigned int doorId, unsigned int targetDoorId, float spawnX, float spawnY)
    : sceneToLoad(sceneToLoad), doorId(doorId), targetDoorId(targetDoorId), spawnPoint(sf::Vector2f(spawnX, spawnY))
{
}

LoadingZone::~LoadingZone()
{
    LoadingZoneManager::unregisterLZ(doorId);
}

void LoadingZone::Start()
{
    Component::Start();
    LoadingZoneManager::registerLZ(this);
    spawnPoint += gameObject->transform.getWorldPosition();
    gameObject->getComponent<Collider>()->setTriggerCallback(
        [this](const std::vector<Collider*>& hits, Collider* trigger)
        {
            for (const auto& hit  : hits)
            {
                if (hit->gameObject->getComponent<PlayerController>())
                    LoadingZoneManager::requestLoading(sceneToLoad, targetDoorId);
            }
        });
}
void LoadingZone::Update(const sf::Time& elapsedTime)
{
    Component::Update(elapsedTime);
}

unsigned int LoadingZone::getDoorID()
{
    return doorId;
}

const sf::Vector2f& LoadingZone::getSpawnPoint() const
{
    return spawnPoint;
}
