//
// Created by Antonin Fruchet on 17/06/2026.
//

#include "TheaterBehavior.h"

#include "scripts/GameManager.h"
#include "scripts/entities/BossFightManager.h"


void TheaterBehavior::Start()
{
    Component::Start();
    if (!GameManager::checkFlag("theater"))
    {
        BossFightManager::init(14, 8, 4, 4.f);
    }
}
void TheaterBehavior::Update(const sf::Time& elapsedTime)
{
    Component::Update(elapsedTime);
    if (!BossFightManager::hasBossSpawned() && BossFightManager::getNbEnemiesToKillBeforeBoss() == 0)
    {
        auto boss = SceneManager::instantiate("resources/prefabs/boss1.xml");
        boss->transform.setLocalPosition({0,0});
        BossFightManager::setBossSpawned();
    }
}


