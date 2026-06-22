//
// Created by Antonin Fruchet on 06/06/2026.
//

#include "EntityController.h"

#include <iostream>
#include <utility>

EntityController::EntityController(float speed, int max_hp, int strength)
    : speed(speed), max_hp(max_hp), current_hp(max_hp), strength(strength)
{
    attackCallback = [this](const std::vector<Collider*>& hits, Collider* trigger)
    {
        for (const auto& hit : hits)
        {
            if (auto controller = hit->gameObject->getComponent<EntityController>(); controller && controller != this)
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
    attackTriggerGO = gameObject->getChild("AttackTrigger");
    attackTriggerGO->getComponent<Collider>()->setTriggerCallback(attackCallback);

    animator = gameObject->getComponent<Animator>();
    if (deathCallback)
    {
        animator->registerAnimationEvent("Death", -1, deathCallback);
    }
    animator->registerAnimationEvent("Slash", -1, [this]() {
        this->endAttack();
    });
    animator->registerAnimationEvent("Hit", -1, [this]() {
        this->invulnerable = false;
    });
}

void EntityController::Update(const sf::Time& elapsedTime)
{
    CharacterController::Update(elapsedTime);
    if (dead && !deathHandled)
    {
        deathHandled = true;
        die();
    }
}


void EntityController::moveEntity(const sf::Vector2f& rawDir, const sf::Time& elapsedTime)
{
    auto nRawDir = rawDir == sf::Vector2f{0,0} ? sf::Vector2f{0,0} : rawDir.normalized();

    // pour un ennemi, la direction n'est jamais vraiment 1, 0 il se retrouve donc
    // toujours a marcher en diagonale si on met pas ce systeme d'epsilon.
    static float const EPSILON = 0.25f;
    if (std::abs(nRawDir.x) > EPSILON || std::abs(nRawDir.y) > EPSILON)
    {
        facing.x = (std::abs(nRawDir.x) <= EPSILON) ? 0.0f : (nRawDir.x / std::abs(nRawDir.x));
        facing.y = (std::abs(nRawDir.y) <= EPSILON) ? 0.0f : (nRawDir.y / std::abs(nRawDir.y));
    }

    if (nRawDir == sf::Vector2f{0,0})
    {
        animator->setParam("moving", false);
    } else
    {
        animator->setParam("moving", true);
        animator->setParam("forwardWalk", facing.y);
        animator->setParam("sideWalk", facing.x);
    }

    auto delta = nRawDir != sf::Vector2f{0,0} ?
    nRawDir*elapsedTime.asSeconds()*speed: sf::Vector2f{0,0};
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
}

void EntityController::endAttack() {
    attackTriggerGO->setActive(false);
    std::cout << "end of attack" << std::endl;

}

void EntityController::takeDamage(int amount) {
    if (invulnerable) return;

    current_hp -= amount;

    std::cout << gameObject->getLabel() << " took " << amount << "damages" << std::endl;
    invulnerable = true;
    animator->setParam("hit", true);
    if (current_hp <= 0) dead=true;
}

void EntityController::die()
{
    std::cout << std::format("{} is dead !", gameObject->getLabel()) << std::endl;
    animator->setParam("dead", true);
}

void EntityController::setDeathCallback(EventCallback callback)
{
    if (animator)
    {
        animator->registerAnimationEvent("Death", -1, callback);
    }
    deathCallback = callback;
}

float EntityController::getHealthRatio() const {
    // On s'assure d'éviter une division par zéro au cas où max_hp serait mal initialisé
    if (max_hp <= 0) return 0.0f;
    return static_cast<float>(current_hp) / max_hp;
}
