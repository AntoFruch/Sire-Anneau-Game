//
// Created by Antonin Fruchet on 11/06/2026.
//

#include "GameManager.h"


PlayerController* GameManager::player;
TextBox* GameManager::textBox{nullptr};

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

void GameManager::registerTB(TextBox* tb)
{
    textBox = tb;
}

void GameManager::unregisterTB(TextBox* tb)
{
    if (tb==textBox)
    {
        textBox = nullptr;
    }
}

PlayerController* GameManager::getPlayer()
{
    return player;
}

TextBox* GameManager::getTB()
{
    return textBox;
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


