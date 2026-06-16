//
// Created by Antonin Fruchet on 11/06/2026.
//

#include "GameManager.h"


PlayerController* GameManager::player;
std::vector<EnemyController*> GameManager::enemies{};

void GameManager::registerPlayer(PlayerController* player)
{
    GameManager::player = player;
}

void GameManager::registerEnemy(EnemyController* ennemy)
{
    enemies.push_back(ennemy);
}

void GameManager::unregisterEnemy(EnemyController* ennemy)
{
    std::erase_if(enemies, [&ennemy](EnemyController* e){return e==ennemy; });
}

PlayerController* GameManager::getPlayer()
{
    return player;
}
