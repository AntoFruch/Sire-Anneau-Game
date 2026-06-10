//
// Created by Antonin Fruchet on 05/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_CONTROLLER_H
#define COMPONENT_BASED_ARCH_CONTROLLER_H
#include "Engine.h"
#include "EntityController.h"

class PlayerController : public EntityController {
    InputAction* moveAction;
    InputAction* attackAction;
    Animator* animator;

    GameObject* attackTriggerGO;
public:
    PlayerController(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize);
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    void takeDamage(int amount) override;

private:
    void attack();
    void endAttack();
};



#endif //COMPONENT_BASED_ARCH_CONTROLLER_H
