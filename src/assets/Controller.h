//
// Created by Antonin Fruchet on 05/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_CONTROLLER_H
#define COMPONENT_BASED_ARCH_CONTROLLER_H
#include "Engine.h"

class Controller : public CharacterController {
    InputAction* moveAction;
    InputAction* createSlimeAction;
    Animator* animator;

    float speed{100};
public:
    Controller(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize);
    ~Controller() override = default;
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;
};



#endif //COMPONENT_BASED_ARCH_CONTROLLER_H
