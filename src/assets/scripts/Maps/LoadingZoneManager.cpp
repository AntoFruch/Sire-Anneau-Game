//
// Created by Antonin Fruchet on 10/06/2026.
//

#include "LoadingZoneManager.h"

std::unordered_map<int, LoadingZone*> LoadingZoneManager::loadingZones;

unsigned int LoadingZoneManager::currentDoorId{0};

void LoadingZoneManager::requestLoading(std::string_view sceneToLoad, unsigned int targetDoorId)
{
    SceneManager::requestLoading(sceneToLoad);
    loadingZones.clear();
    currentDoorId = targetDoorId;
}

bool LoadingZoneManager::defaultSpawn()
{
    return !loadingZones.contains(currentDoorId);
}

const sf::Vector2f& LoadingZoneManager::getSpawnPointFromCurrentDoorId()
{
    return loadingZones.at(currentDoorId)->getSpawnPoint();
}

void LoadingZoneManager::registerLZ(LoadingZone* lz)
{
    loadingZones.try_emplace(lz->getDoorID(), lz);
}

