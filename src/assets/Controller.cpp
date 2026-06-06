//
// Created by Antonin Fruchet on 05/06/2026.
//

#include "Controller.h"

#include <iostream>

#include "Managers/Input/InputManager.h"

// --- ENREGISTREMENT AUTOMATIQUE ---
// On crée une variable globale/statique anonyme.
// Son seul but est de s'exécuter AVANT le début du jeu pour enregistrer le composant.
namespace {
    const bool registered = []() {
        ComponentFactory::Register("Controller", [](const pugi::xml_node& node) {
            return std::make_unique<Controller>(
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

Controller::Controller(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize)
    : CharacterController(colliderPos, colliderSize)
{}

void Controller::Start()
{
    CharacterController::Start();
    moveAction = InputManager::findAction("Move");
    animator = gameObject->getComponent<Animator>();
}

void Controller::Update(const sf::Time& elapsedTime)
{
    CharacterController::Update(elapsedTime);
    auto rawDir = moveAction->ReadValue<sf::Vector2f>();
    auto delta = rawDir != sf::Vector2f{0,0} ?
    rawDir.normalized()*elapsedTime.asSeconds()*speed: sf::Vector2f{0,0};

    move(delta);
    if (rawDir == sf::Vector2f{0,0})
    {
        animator->setParam("moving", false);
    } else
    {
        animator->setParam("moving", true);
        animator->setParam("forwardWalk", rawDir.y);
        animator->setParam("sideWalk", rawDir.x);
    }
}
