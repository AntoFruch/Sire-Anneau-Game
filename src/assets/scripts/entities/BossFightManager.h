//
// Created by Antonin Fruchet on 20/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_BOSSFIGHTMANAGER_H
#define COMPONENT_BASED_ARCH_BOSSFIGHTMANAGER_H
#include "EnemyController.h"


class BossFightManager {

    static bool inFight;
    static bool bossSpawned;

    static int nbEnemiesToKill;
    static int nbEnemiesToKillBeforeBoss;
    static int maxAliveEnemies;
    static float enemiesSpawnRate;

    static std::vector<EnemyController*> enemies;
public:
    static void init(int nbEnemiesToKill, int nbEnemiesToKillBeforeBoss, int maxAliveEnemies, float enemiesSpawnRate);
    static void end();

    static void registerEnemy(EnemyController*);
    static void unregisterEnemy(const EnemyController*);
    static int getNbEnemiesToKill();
    static int getNbEnemiesToKillBeforeBoss();
    static int getMaxAliveEnemies();
    static float getEnemiesSpawnRate();
    static bool hasBossSpawned();
    static void setBossSpawned();
    static bool isInFight();

};


#endif //COMPONENT_BASED_ARCH_BOSSFIGHTMANAGER_H
