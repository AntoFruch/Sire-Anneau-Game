//
// Created by Antonin Fruchet on 11/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_ENEMYCONTROLLER_H
#define COMPONENT_BASED_ARCH_ENEMYCONTROLLER_H


#include "Engine.h"
#include "Managers/Scene/ComponentFactory.h"
#include "EntityController.h"

class EnemyController : public EntityController {
    enum State { Wander, Chasing, Attack };
    State currentState {Wander};

    float wanderTime{2.f};
    float wanderClock{wanderTime};
    sf::Vector2f headingDirection;

    float chasingDistance{200};

    float attackClock;
    float attackTime{0.8f};
    float attackDistance{40};

public:
    EnemyController(float speed, int max_hp, int strength, float attackSpeed, float attackRange, float chasingRange);
    ~EnemyController() override;
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

private:
    static inline bool s_registered = ComponentFactory::Register("EnemyController", [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
        return std::make_unique<EnemyController>(
            node.attribute("speed").as_float(),
            node.attribute("max_hp").as_int(),
            node.attribute("strength").as_int(),
            node.attribute("attackSpeed").as_float(),
            node.attribute("attackRange").as_float(),
            node.attribute("chasingRange").as_float()
        );
    });
};



#endif //COMPONENT_BASED_ARCH_ENEMYCONTROLLER_H
