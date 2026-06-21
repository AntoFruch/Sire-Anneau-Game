//
// Created by Antonin Fruchet on 16/06/2026.
//

#include "BossController.h"

BossController::BossController(float speed, int max_hp, int strength, float attackSpeed, float attackRange, float chasingRange)
    : EnemyController(speed, max_hp, strength, attackSpeed, attackRange, chasingRange)
{

}

BossController::~BossController()
{
}

void BossController::Start()
{
    EnemyController::Start();
}
void BossController::Update(const sf::Time& elapsedTime)
{
    EnemyController::Update(elapsedTime);
}

void BossController::die()
{
    EntityController::die();
}
