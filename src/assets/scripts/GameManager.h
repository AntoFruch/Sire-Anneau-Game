//
// Created by Antonin Fruchet on 11/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_GAMEMANAGER_H
#define COMPONENT_BASED_ARCH_GAMEMANAGER_H
#include "entities/EnemyController.h"
#include "entities/PlayerController.h"
#include "UI/HUD/TextBox.h"


class GameManager {
    static PlayerController* player;
    static std::vector<EnemyController*> enemies;

    static TextBox* textBox;

    static std::unordered_map<std::string, bool> flags;

public:
    static void registerPlayer(PlayerController*);
    static void unregisterPlayer(PlayerController*);
    static void registerEnemy(EnemyController*);
    static void unregisterEnemy(const EnemyController*);
    static void registerTB(TextBox*);
    static void unregisterTB(TextBox*);

    static std::vector<EnemyController*> getEnemies();
    static PlayerController* getPlayer();
    static TextBox* getTB();

    static void setFlag(const std::string& flagName);
    static bool checkFlag(const std::string& flagName);
};



#endif //COMPONENT_BASED_ARCH_GAMEMANAGER_H
