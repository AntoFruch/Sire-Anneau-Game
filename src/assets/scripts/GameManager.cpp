//
// Created by Antonin Fruchet on 11/06/2026.
//

#include "GameManager.h"


PlayerController* GameManager::player;
std::vector<EnemyController*> GameManager::enemies{};

std::unordered_map<std::string, bool> GameManager::flags{
    {"theater", false},
    {"balcony", false},
    {"other", false},
};

void GameManager::registerPlayer(PlayerController* player)
{
    GameManager::player = player;
}

void GameManager::unregisterPlayer(PlayerController*player)
{
    if (GameManager::player == player)
    {
        GameManager::player = nullptr;
    }
}

void GameManager::registerEnemy(EnemyController* enemy)
{
    enemies.push_back(enemy);
}

void GameManager::unregisterEnemy(const EnemyController* enemy)
{
    std::erase_if(enemies, [&enemy](const EnemyController* e){return e==enemy; });
}

PlayerController* GameManager::getPlayer()
{
    return player;
}

std::vector<EnemyController*> GameManager::getEnemies() {
    return enemies;
}

void GameManager::setFlag(const std::string& flagName)
{
    if (flags.contains(flagName))
    {
        flags[flagName] = true;
        std::cout << std::format("{} flag now set on {}", flagName, flags[flagName]) << std::endl;
    }
}

bool GameManager::checkFlag(const std::string& flagName)
{
    return flags[flagName];
}


