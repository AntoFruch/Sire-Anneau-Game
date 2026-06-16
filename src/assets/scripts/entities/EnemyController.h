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

private:
    static inline bool s_registered = ComponentFactory::Register("EnemyController", [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
        return std::make_unique<EnemyController>(
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
};



#endif //COMPONENT_BASED_ARCH_ENEMYCONTROLLER_H
