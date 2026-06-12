//
// Created by Antonin Fruchet on 11/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_ENEMYCONTROLLER_H
#define COMPONENT_BASED_ARCH_ENEMYCONTROLLER_H


#include "Engine.h"
#include "EntityController.h"

class EnemyController : public EntityController {
    enum State { Wander, Chasing, Attack };
    State currentState {Wander};

    float wanderClock;
    float wanderTime{2.f};
    sf::Vector2f headingDirection;
    float chasingDistance{100};
    float attackDistance{40 };

public:
    EnemyController(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize, float speed, int max_hp, int strength);
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    void takeDamage(int amount) override;
};



#endif //COMPONENT_BASED_ARCH_ENEMYCONTROLLER_H
