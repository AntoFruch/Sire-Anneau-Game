//
// Created by Antonin Fruchet on 06/06/2026.
//

#include "EntityController.h"

#include <iostream>

EntityController::EntityController(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize, float speed)
    : CharacterController(colliderPos, colliderSize), speed(speed)
{
    attackCallback = [](const std::vector<Collider*>& hits, Collider* trigger)
    {
        for (const auto& hit : hits)
        {
            if (auto controller = hit->gameObject->getComponent<EntityController>())
            {
                std::cout << hit->gameObject->getLabel() << std::endl;
                controller->takeDamage(); // tester si ça marche avec des ennemis
            }
        }
    };
}
void EntityController::Start()
{
    CharacterController::Start();
}

void EntityController::Update(const sf::Time& elapsedTime)
{
    CharacterController::Update(elapsedTime);
}


void EntityController::moveEntity(const sf::Vector2f& rawDir, const sf::Time& elapsedTime)
{
    if (rawDir!=sf::Vector2f{0,0})
    {
        facing.x = rawDir.x == 0 ? 0 : rawDir.x / abs(rawDir.x);
        facing.y = rawDir.y == 0 ? 0 : rawDir.y / abs(rawDir.y);
    }

    auto delta = rawDir != sf::Vector2f{0,0} ?
    rawDir.normalized()*elapsedTime.asSeconds()*speed: sf::Vector2f{0,0};
    move(delta);
}
