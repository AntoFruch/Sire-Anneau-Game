//
// Created by alexis on 6/17/26.
//

#include "EnnemySpawner.h"

#include "EnemyController.h"
#include "Managers/Collisions/CollisionsManager.h"
#include "scripts/GameManager.h"

EnnemySpawner::EnnemySpawner(std::string_view ennemyName, float intervalle) {
  this->ennemyName = ennemyName;
  this->intervalle = intervalle;
}

void EnnemySpawner::Start() {
  Component::Start();
  this->triggerZone = gameObject->getComponent<Collider>();
}

void EnnemySpawner::Update(const sf::Time &elapsedTime) {
  Component::Update(elapsedTime);
  SpawnClock += elapsedTime.asSeconds();
  if (SpawnClock >= intervalle) {
    std::vector<Collider*> triggerers = CollisionsManager::checkTrigger(*this->triggerZone);
    if (triggerers.empty()) {
      GameObject* Ennemy = SceneManager::instantiate(ennemyName);
      Transform spawnerTransform = gameObject->transform;
      sf::Vector2f spawnPosition = spawnerTransform.getWorldPosition();
      Ennemy->transform.setLocalPosition(spawnPosition);







      SpawnClock = 0;
    }
  }
}

