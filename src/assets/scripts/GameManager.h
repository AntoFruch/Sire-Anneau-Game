//
// Created by Antonin Fruchet on 11/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_GAMEMANAGER_H
#define COMPONENT_BASED_ARCH_GAMEMANAGER_H
#include "entities/EnemyController.h"
#include "entities/PlayerController.h"


class GameManager {
    static PlayerController* player;
    static std::vector<EnemyController*> enemies;

    static std::unordered_map<std::string, bool> flags;

public:
    static void registerPlayer(PlayerController*);
    static void unregisterPlayer(PlayerController*);
    static void registerEnemy(EnemyController*);
    static void unregisterEnemy(const EnemyController*);

    static void setFlag(const std::string& flagName);
    static bool checkFlag(const std::string& flagName);

    static PlayerController* getPlayer();
};



#endif //COMPONENT_BASED_ARCH_GAMEMANAGER_H
