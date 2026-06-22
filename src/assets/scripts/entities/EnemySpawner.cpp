//
// Created by alexis on 6/17/26.
//

#include "EnemySpawner.h"

#include "scripts/Maps/BossFightController.h"
#include "EnemyController.h"
#include "Managers/Collisions/CollisionsManager.h"

EnemySpawner::EnemySpawner(std::string_view ennemyName) {
  this->ennemyName = ennemyName;
}

void EnemySpawner::Start() {
  Component::Start();
  static int cnt = 0;
  std::cout << std::format("init spawner {}\n", ++cnt);
  this->triggerZone = gameObject->getComponent<Collider>();
  if (auto* bossFight = BossFightController::getActiveFight())
  {
    bossFight->registerSpawner(this);
  }
}

void EnemySpawner::Update(const sf::Time &elapsedTime) {
  Component::Update(elapsedTime);
  SpawnClock += elapsedTime.asSeconds();
}

bool EnemySpawner::isReady(float spawnInterval) const
{
  return SpawnClock >= spawnInterval;
}

bool EnemySpawner::isFree() const
{
  return CollisionsManager::checkTrigger(*triggerZone).empty();
}

GameObject* EnemySpawner::spawn()
{
  GameObject* enemy = SceneManager::instantiate(ennemyName);
  const sf::Vector2f spawnPosition = gameObject->transform.getWorldPosition();
  enemy->transform.setLocalPosition(spawnPosition);
  return enemy;
}

void EnemySpawner::resetClock()
{
  SpawnClock = 0;
}
