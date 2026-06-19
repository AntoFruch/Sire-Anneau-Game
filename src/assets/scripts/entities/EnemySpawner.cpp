//
// Created by alexis on 6/17/26.
//

#include "EnemySpawner.h"

#include "BossFightManager.h"
#include "EnemyController.h"
#include "Managers/Collisions/CollisionsManager.h"
#include "scripts/GameManager.h"

EnemySpawner::EnemySpawner(std::string_view ennemyName, float intervalle) {
  this->ennemyName = ennemyName;
  this->intervalle = intervalle;
}

void EnemySpawner::Start() {
  Component::Start();
  this->triggerZone = gameObject->getComponent<Collider>();
}

void EnemySpawner::Update(const sf::Time &elapsedTime) {
  Component::Update(elapsedTime);
  if (!BossFightManager::isInFight()) return;

  SpawnClock += elapsedTime.asSeconds();

  if (SpawnClock >= BossFightManager::getEnemiesSpawnRate()) {
    std::vector<Collider*> triggerers = CollisionsManager::checkTrigger(*this->triggerZone);

    if (triggerers.empty()) {
      GameObject* Ennemy = SceneManager::instantiate(ennemyName);
      BossFightManager::registerEnemy(Ennemy->getComponent<EnemyController>());
      Transform spawnerTransform = gameObject->transform;
      sf::Vector2f spawnPosition = spawnerTransform.getWorldPosition();
      Ennemy->transform.setLocalPosition(spawnPosition);

      SpawnClock = 0;
    }
  }
}

