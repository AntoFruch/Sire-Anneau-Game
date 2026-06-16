//
// Created by Antonin Fruchet on 11/06/2026.
//

#include "EnemyController.h"

#include <random>

#include "scripts/GameManager.h"

EnemyController::EnemyController(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize, float speed, int max_hp, int strength)
    : EntityController(colliderPos, colliderSize, speed, max_hp, strength)
{
}

void EnemyController::Start()
{
    EntityController::Start();
}

sf::Vector2f random_vector2f_minus1_to_1() {
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    // On génère des entiers -1, 0 ou 1
    static std::uniform_int_distribution<int> distribution(-1, 1);

    // SFML convertit automatiquement les int en float dans le constructeur de sf::Vector2f
    return sf::Vector2f(distribution(engine), distribution(engine));
}

void EnemyController::Update(const sf::Time& elapsedTime)
{
    EntityController::Update(elapsedTime);
    sf::Vector2f toPlayer = GameManager::getPlayer()->gameObject->transform.getWorldPosition() - gameObject->transform.getWorldPosition();
    float distanceSquared = toPlayer.x*toPlayer.x + toPlayer.y*toPlayer.y;
    switch (currentState)
    {
    case Wander:
        wanderClock+=elapsedTime.asSeconds();
        if (wanderClock >= wanderTime)
        {
            wanderClock = 0;
            headingDirection = random_vector2f_minus1_to_1();
        }
        moveEntity(headingDirection, elapsedTime);
        if (distanceSquared <= chasingDistance*chasingDistance) currentState = Chasing;
        break;
    case Chasing:
        moveEntity(toPlayer, elapsedTime);
        if (distanceSquared <= attackDistance*attackDistance) currentState = Attack;
        if (distanceSquared > chasingDistance*chasingDistance) currentState = Wander;
        break;
    case Attack:
        attack();
        if (distanceSquared > attackDistance*attackDistance) currentState = Chasing;
        break;
    }
}

void EnemyController::takeDamage(int amount)
{
    EntityController::takeDamage(amount);
}
