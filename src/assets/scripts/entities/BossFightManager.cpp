//
// Created by Antonin Fruchet on 20/06/2026.
//

#include "BossFightManager.h"

bool BossFightManager::inFight{false};
bool BossFightManager::bossSpawned{false};
int BossFightManager::nbEnemiesToKill;
int BossFightManager::nbEnemiesToKillBeforeBoss;
int BossFightManager::maxAliveEnemies;
float BossFightManager::enemiesSpawnRate;

std::vector<EnemyController*> BossFightManager::enemies{};

void BossFightManager::init(int nbEnemiesToKill, int nbEnemiesToKillBeforeBoss, int maxAliveEnemies,
    float enemiesSpawnRate)
{
    BossFightManager::nbEnemiesToKill = nbEnemiesToKill;
    BossFightManager::nbEnemiesToKillBeforeBoss = nbEnemiesToKillBeforeBoss;
    BossFightManager::maxAliveEnemies = maxAliveEnemies;
    BossFightManager::enemiesSpawnRate = enemiesSpawnRate;
    inFight=true;
}

void BossFightManager::end()
{
    inFight=false;
}

void BossFightManager::registerEnemy(EnemyController* enemy)
{
    enemies.push_back(enemy);
}

void BossFightManager::unregisterEnemy(const EnemyController* enemy)
{
    std::erase_if(enemies, [&enemy](const EnemyController* e)
    {
        nbEnemiesToKill--;
        if (nbEnemiesToKill<0) end();
        if (nbEnemiesToKillBeforeBoss > 0) nbEnemiesToKillBeforeBoss--;
        return e==enemy;
    });
}


int BossFightManager::getNbEnemiesToKill()
{
    return nbEnemiesToKill;
}

int BossFightManager::getNbEnemiesToKillBeforeBoss()
{
    return nbEnemiesToKillBeforeBoss;
}

int BossFightManager::getMaxAliveEnemies()
{
    return maxAliveEnemies;
}

float BossFightManager::getEnemiesSpawnRate()
{
    return enemiesSpawnRate;
}

bool BossFightManager::hasBossSpawned()
{
    return bossSpawned;
}

void BossFightManager::setBossSpawned()
{
    bossSpawned =true;
}

bool BossFightManager::isInFight()
{
    return inFight;
}
