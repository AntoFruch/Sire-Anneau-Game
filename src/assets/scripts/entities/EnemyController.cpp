//
// Created by Antonin Fruchet on 11/06/2026.
//

#include "EnemyController.h"

#include <random>

#include "scripts/GameManager.h"

EnemyController::EnemyController(float speed, int max_hp, int strength,
    float attackSpeed,
    float attackRange,
    float chasingRange)
    : EntityController(speed, max_hp, strength),
        chasingDistance(chasingRange),
        attackTime(1/attackSpeed),
        attackDistance(attackRange)
{
}

EnemyController::~EnemyController()
{
}

void EnemyController::Start()
{
    EntityController::Start();
    static int cnt=0;
    std::cout << ++cnt<< std::endl;
}

sf::Vector2f random_vector2f_minus1_to_1() {
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    static std::uniform_int_distribution distribution(-1, 1);

    return sf::Vector2f(distribution(engine), distribution(engine));
}

void EnemyController::Update(const sf::Time& elapsedTime)
{
    EntityController::Update(elapsedTime);
    if (dead) return;

    float distanceSquared;
    sf::Vector2f toPlayer;
    if (GameManager::getPlayer())
    {
        toPlayer = GameManager::getPlayer()->gameObject->transform.getWorldPosition() - gameObject->transform.getWorldPosition();
        distanceSquared = toPlayer.x*toPlayer.x + toPlayer.y*toPlayer.y;
    } else
    {
        distanceSquared = 2*chasingDistance*chasingDistance;
    }

    // Machine a état
    switch (currentState)
    {
    case Wander:
        wanderClock+=elapsedTime.asSeconds();
        if (wanderClock >= wanderTime)
        {
            wanderClock = 0;
            facing = random_vector2f_minus1_to_1();
        }
        moveEntity(facing, elapsedTime);
        if (distanceSquared <= chasingDistance*chasingDistance) currentState = Chasing;
        break;
    case Chasing:
        moveEntity(toPlayer, elapsedTime);
        if (distanceSquared <= attackDistance*attackDistance) currentState = Attack;
        if (distanceSquared > chasingDistance*chasingDistance) currentState = Wander;
        break;
    case Attack:
        attackClock+=elapsedTime.asSeconds();
        if (attackClock>=attackTime)
        {
            attackClock = 0;
            attack();
        }
        if (distanceSquared > attackDistance*attackDistance)
        {
            currentState = Chasing;
            attackClock=0;
        }
        break;
    }
}
