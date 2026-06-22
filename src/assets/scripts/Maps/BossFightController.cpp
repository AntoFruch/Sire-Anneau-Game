//
// Created by Antonin Fruchet on 21/06/2026.
//

#include "BossFightController.h"

#include "scripts/GameManager.h"
#include "scripts/entities/BossController.h"
#include "scripts/entities/EnemyController.h"
#include "scripts/entities/EnemySpawner.h"
#include "scripts/entities/EntityController.h"

BossFightController* BossFightController::activeFight{nullptr};

BossFightController::BossFightController(
    std::string_view completionFlag,
    const std::vector<std::string>& textOnComplete,
    std::string_view bossPrefab,
    float bossX,
    float bossY,
    int totalEnemiesToSpawn,
    int killsBeforeBoss,
    int maxAliveEnemies,
    float spawnInterval)
    : completionFlag(completionFlag),
      textOnComplete(textOnComplete),
      bossPrefab(bossPrefab),
      bossSpawnPosition(bossX, bossY),
      totalEnemiesToSpawn(totalEnemiesToSpawn),
      killsBeforeBoss(killsBeforeBoss),
      maxAliveEnemies(maxAliveEnemies),
      spawnInterval(spawnInterval)
{
}

BossFightController::~BossFightController()
{
    if (activeFight == this)
    {
        activeFight = nullptr;
    }
}

void BossFightController::Start()
{
    Component::Start();
    activeFight = this;

    if (GameManager::checkFlag(completionFlag))
    {
        state = State::Completed;
        return;
    }

    state = State::Waves;
}

void BossFightController::Update(const sf::Time& elapsedTime)
{
    Component::Update(elapsedTime);

    switch (state)
    {
    case State::Waves:
        updateWaves();
        break;
    case State::Boss:
        updateBoss();
        break;
    case State::Inactive:
    case State::Completed:
        break;
    }
}

BossFightController* BossFightController::getActiveFight()
{
    return activeFight;
}

void BossFightController::registerSpawner(EnemySpawner* spawner)
{
    if (state == State::Completed || spawner == nullptr)
    {
        return;
    }

    spawners.push_back(spawner);
}

int BossFightController::getTotalEnemies() const
{
    return totalEnemiesToSpawn;
}

int BossFightController::getKilledEnemies() const
{
    return killedEnemies;
}

bool BossFightController::isCompleted() const
{
    return state == State::Completed;
}

void BossFightController::updateWaves()
{
    trySpawnEnemy();

    if (killedEnemies >= killsBeforeBoss)
    {
        spawnBoss();
        state = State::Boss;
    }
}

void BossFightController::updateBoss()
{
    if (bossDead &&
        killedEnemies >= totalEnemiesToSpawn &&
        aliveEnemies.empty())
    {
        completeFight();
        return;
    }

    trySpawnEnemy();
}

void BossFightController::trySpawnEnemy()
{
    if (spawnedEnemies >= totalEnemiesToSpawn ||
        static_cast<int>(aliveEnemies.size()) >= maxAliveEnemies)
    {
        return;
    }

    for (EnemySpawner* spawner : spawners)
    {
        if (spawnedEnemies >= totalEnemiesToSpawn ||
            static_cast<int>(aliveEnemies.size()) >= maxAliveEnemies)
        {
            return;
        }

        if (!spawner->isReady(spawnInterval) || !spawner->isFree())
        {
            continue;
        }

        GameObject* enemyObject = spawner->spawn();
        auto* enemy = enemyObject->getComponent<EnemyController>();
        if (enemy == nullptr)
        {
            spawner->resetClock();
            continue;
        }

        aliveEnemies.push_back(enemy);
        spawnedEnemies++;
        spawner->resetClock();

        enemy->setDeathCallback([this, enemy]()
        {
            std::erase(aliveEnemies, enemy);

            killedEnemies++;
            enemy->gameObject->destroySelf();
        });
    }
}

void BossFightController::spawnBoss()
{
    GameObject* bossObject = SceneManager::instantiate(bossPrefab);
    bossObject->transform.setLocalPosition(bossSpawnPosition);
    boss = bossObject->getComponent<BossController>();

    if (boss != nullptr)
    {
        boss->setDeathCallback([this]()
        {
            bossDead = true;
            boss->gameObject->destroySelf();
        });
    }
}

void BossFightController::completeFight()
{
    GameManager::setFlag(completionFlag);
    state = State::Completed;

    auto tb = GameManager::getTB();
    tb->setBuffer(textOnComplete);
    tb->open();
}


