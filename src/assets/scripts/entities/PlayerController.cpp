//
// Created by Antonin Fruchet on 05/06/2026.
//

#include "PlayerController.h"

#include <iostream>

#include "Managers/Input/InputManager.h"
#include "scripts/GameManager.h"
#include "scripts/Maps/LoadingZoneManager.h"

PlayerController::PlayerController(float speed, int max_hp, int strength)
    : EntityController(speed, max_hp, strength)
{}

PlayerController::~PlayerController()
{
    GameManager::unregisterPlayer(this);
}
void PlayerController::Start()
{
    EntityController::Start();
    moveAction = InputManager::findAction("Move");
    attackAction = InputManager::findAction("Attack");

    if (!LoadingZoneManager::defaultSpawn())
    {
        gameObject->transform.setLocalPosition(LoadingZoneManager::getSpawnPointFromCurrentDoorId());
    }

    GameManager::registerPlayer(this);
}

void PlayerController::Update(const sf::Time& elapsedTime)
{
    EntityController::Update(elapsedTime);
    if (dead) return;

    auto rawDir = moveAction->ReadValue<sf::Vector2f>();
    moveEntity(rawDir, elapsedTime);

    if (attackAction->wasPerformedThisFrame())
    {
        attack();
    }
}

void PlayerController::takeDamage(int amount)
{
    EntityController::takeDamage(amount); // la logique des dégâts subis
}

void PlayerController::attack()
{
    EntityController::attack();
}
