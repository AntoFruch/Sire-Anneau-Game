//
// Created by Antonin Fruchet on 10/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_LOADINGZONEMANAGER_H
#define COMPONENT_BASED_ARCH_LOADINGZONEMANAGER_H
#include "Engine.h"
#include <string_view>

#include "LoadingZone.h"


class LoadingZoneManager {

    static std::unordered_map<int, LoadingZone*> loadingZones;

    // la porte d'où on vient dans la scene actuelle
    static unsigned int currentDoorId;

public:
    void static requestLoading(std::string_view sceneToLoad, unsigned int targetDoorId);
    static const sf::Vector2f& getSpawnPointFromCurrentDoorId();
    static void registerLZ(LoadingZone* lz);
    static bool defaultSpawn();
};



#endif //COMPONENT_BASED_ARCH_LOADINGZONEMANAGER_H
