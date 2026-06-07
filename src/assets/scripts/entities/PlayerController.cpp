//
// Created by Antonin Fruchet on 05/06/2026.
//

#include "PlayerController.h"

#include <iostream>

#include "Managers/Input/InputManager.h"
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
                });
        });
        return true;
    }();
}
// --------------------------

PlayerController::PlayerController(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize)
    : EntityController(colliderPos, colliderSize, 100)
{}

void PlayerController::Start()
{
    CharacterController::Start();
    moveAction = InputManager::findAction("Move");
    attackAction = InputManager::findAction("Attack");
    animator = gameObject->getComponent<Animator>();
    attackTriggerGO = gameObject->getChild("AttackTrigger");
}

void PlayerController::Update(const sf::Time& elapsedTime)
{
    CharacterController::Update(elapsedTime);
    auto rawDir = moveAction->ReadValue<sf::Vector2f>();
    moveEntity(rawDir, elapsedTime);

    if (rawDir == sf::Vector2f{0,0})
    {
        animator->setParam("moving", false);
    } else
    {
        animator->setParam("moving", true);
        animator->setParam("forwardWalk", rawDir.y);
        animator->setParam("sideWalk", rawDir.x);
    }

    if (attackAction->wasPerformedThisFrame())
    {
        attack();
    } else
    {
        attackTriggerGO->transform.set_position({0,0});
        attackTriggerGO->getComponent<Collider>()->setTriggerActivationState(false);
    }
}

void PlayerController::attack()
{
    animator->setParam("attack", true);
    attackTriggerGO->transform.set_position({
        facing.x * gameObject->getComponent<Collider>()->getSize().x,
        facing.y * gameObject->getComponent<Collider>()->getSize().y,
    });
    attackTriggerGO->getComponent<Collider>()->setTriggerCallback(attackCallback);
    attackTriggerGO->getComponent<Collider>()->setTriggerActivationState(true);
}

void PlayerController::takeDamage()
{
    std::cout << "damage taken !" << std::endl;
}
