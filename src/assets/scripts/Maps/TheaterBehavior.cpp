//
// Created by Antonin Fruchet on 17/06/2026.
//

#include "TheaterBehavior.h"

#include "scripts/GameManager.h"


void TheaterBehavior::Start()
{
    Component::Start();
    if (!GameManager::checkFlag("theater"))
    {
        auto boss = SceneManager::instantiate("resources/prefabs/boss1.xml");
        boss->transform.setLocalPosition({0,0});

        // instancier les spawners etc
    }
}
void TheaterBehavior::Update(const sf::Time& elapsedTime)
{
    Component::Update(elapsedTime);
}


