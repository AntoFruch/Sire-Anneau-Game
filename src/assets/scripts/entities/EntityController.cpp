//
// Created by Antonin Fruchet on 06/06/2026.
//

#include "EntityController.h"

#include <iostream>

EntityController::EntityController(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize, float speed, int max_hp, int strength)
    : CharacterController(colliderPos, colliderSize), speed(speed), max_hp(max_hp), current_hp(max_hp), strength(strength)
{
    attackCallback = [this](const std::vector<Collider*>& hits, Collider* trigger)
    {
        for (const auto& hit : hits)
        {
            if (auto controller = hit->gameObject->getComponent<EntityController>())
            {
                std::cout << "Attacker : " << trigger->gameObject->getLabel() << std::endl;
                controller->takeDamage(this->strength); // tester si ça marche avec des ennemis
            }
        }
    };
}
void EntityController::Start()
{
    CharacterController::Start();
    animator = gameObject->getComponent<Animator>();
    animator->registerAnimationEvent("Slash", 3, [this]() {
        this->endAttack();
    });
    animator->registerAnimationEvent("Hit", 0, [this]() {
        this->invulnerable = false;
    });
    animator->registerAnimationEvent("Death", 3, [this]() {
        gameObject->destroySelf();
    });
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

    if (rawDir == sf::Vector2f{0,0})
    {
        animator->setParam("moving", false);
    } else
    {
        animator->setParam("moving", true);
        animator->setParam("forwardWalk", rawDir.y);
        animator->setParam("sideWalk", rawDir.x);
    }

    auto delta = rawDir != sf::Vector2f{0,0} ?
    rawDir.normalized()*elapsedTime.asSeconds()*speed: sf::Vector2f{0,0};
    move(delta);
}

void EntityController::attack()
{
    animator->setParam("attack", true);
    attackTriggerGO->setActive(true);
    attackTriggerGO->transform.setLocalPosition({
        facing.x * gameObject->getComponent<Collider>()->getSize().x,
        facing.y * gameObject->getComponent<Collider>()->getSize().y,
    });
    attackTriggerGO->getComponent<Collider>()->setTriggerCallback(attackCallback);
}

void EntityController::endAttack() {
    attackTriggerGO->setActive(false);
    std::cout << "end of attack" << std::endl;

}

void EntityController::takeDamage(int amount) {
    if (invulnerable) return;

    if (current_hp <= 0) current_hp = 0 ;
    else {current_hp -= amount;}

    // vérification de mort
    if (current_hp<=0) { // Player est mort !
        std::cout << "Player is dead !" << std::endl;
        animator->setParam("dead", true);

    }
    else {// Player encore en vie
        std::cout << gameObject->getLabel() << " took " << amount << "damages" << std::endl;
        invulnerable = true;
        animator->setParam("hit", true);
    }
}

float EntityController::getHealthRatio() const {
    // On s'assure d'éviter une division par zéro au cas où max_hp serait mal initialisé
    if (max_hp <= 0) return 0.0f;
    return static_cast<float>(current_hp) / max_hp;
}