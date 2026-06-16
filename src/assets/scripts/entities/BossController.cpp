//
// Created by Antonin Fruchet on 16/06/2026.
//

#include "BossController.h"

#include "scripts/GameManager.h"

BossController::BossController(float speed, int max_hp, int strength)
    : EnemyController(speed, max_hp, strength)
{

}

BossController::~BossController()
{
    GameManager::setFlag("theater");
}

void BossController::Start()
{
    EnemyController::Start();
}
void BossController::Update(const sf::Time& elapsedTime)
{
    EnemyController::Update(elapsedTime);
}

