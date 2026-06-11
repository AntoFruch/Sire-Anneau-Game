//
// Created by Antonin Fruchet on 05/06/2026.
//

#include "PlayerController.h"
#include "../HUD/HUDManager.h"

#include <iostream>

#include "Managers/Input/InputManager.h"
#include "scripts/GameManager.h"
#include "scripts/Maps/LoadingZoneManager.h"
// --- ENREGISTREMENT AUTOMATIQUE ---
// On crée une variable globale/statique anonyme.
// Son seul but est de s'exécuter AVANT le début du jeu pour enregistrer le composant.
namespace {
    const bool registered = []() {
        ComponentFactory::Register("PlayerController", [](const pugi::xml_node& node) {
            return std::make_unique<PlayerController>(
                sf::Vector2f{
                    node.attribute("colliderX").as_float(),
                    node.attribute("colliderY").as_float()
                },
                sf::Vector2f{
                    node.attribute("colliderW").as_float(),
                    node.attribute("colliderH").as_float()
                },
                node.attribute("speed").as_float(),
                node.attribute("max_hp").as_int(),
                node.attribute("strength").as_int()
                );
        });
        return true;
    }();
}
// --------------------------

PlayerController::PlayerController(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize, float speed, int max_hp, int strength)
    : EntityController(colliderPos, colliderSize, speed, max_hp, strength)
{}

void PlayerController::Start()
{
    EntityController::Start();
    moveAction = InputManager::findAction("Move");
    attackAction = InputManager::findAction("Attack");
    attackTriggerGO = gameObject->getChild("AttackTrigger");

    if (!LoadingZoneManager::defaultSpawn())
    {
        gameObject->transform.setLocalPosition(LoadingZoneManager::getSpawnPointFromCurrentDoorId());
    }

    HUDManager::registerPlayer(this);
    GameManager::registerPlayer(this);
}

void PlayerController::Update(const sf::Time& elapsedTime)
{
    EntityController::Update(elapsedTime);
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

