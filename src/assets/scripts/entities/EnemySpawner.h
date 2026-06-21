//
// Created by alexis on 6/17/26.
//

#ifndef SIRE_ANNEAU_GAME_ENNEMYSPAWNER_H
#define SIRE_ANNEAU_GAME_ENNEMYSPAWNER_H
#include "Engine.h"


class EnemySpawner : public Component // Possible to inherit a class that already inherits Component
{
  float intervalle;
  float SpawnClock{0};
  std::string ennemyName;
  Collider* triggerZone;

public:
  EnemySpawner(std::string_view ennemyName, float intervalle);
  void Start() override; // Executed once at the beginning when everything's constructed
  void Update(const sf::Time& elapsedTime) override; // Executed every frame
  [[nodiscard]] bool isReady(float spawnInterval) const;
  [[nodiscard]] bool isFree() const;
  GameObject* spawn();
  void resetClock();

private:
  static inline bool s_registered = ComponentFactory::Register("EnemySpawner", [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
      return std::make_unique<EnemySpawner>(
        node.attribute("ennemyName").as_string(),
        node.attribute("intervalle").as_float()
      );
  });
};


#endif //SIRE_ANNEAU_GAME_ENNEMYSPAWNER_H
