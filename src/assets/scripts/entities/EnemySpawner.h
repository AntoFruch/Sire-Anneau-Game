//
// Created by alexis on 6/17/26.
//

#ifndef SIRE_ANNEAU_GAME_ENNEMYSPAWNER_H
#define SIRE_ANNEAU_GAME_ENNEMYSPAWNER_H
#include "Engine.h"

/**
 * @brief Spawner d'ennemis controllable
 */
class EnemySpawner : public Component // Possible to inherit a class that already inherits Component
{
  float SpawnClock{0};
  std::string ennemyName; // chemin vers le prefab de l'ennemi a faire apparaitre
  Collider* triggerZone;  // pointeur vers la zone trigger qui permet de savoir s'il y a un objet sur le spawner ou non

public:
  EnemySpawner(std::string_view ennemyName);
  void Start() override;
  void Update(const sf::Time& elapsedTime) override;

  /**
   *
   * @param spawnInterval
   * @return true si le spawner est prêt à faire apparaître un enemi, false sinon
   */
  [[nodiscard]] bool isReady(float spawnInterval) const;
  /**
   *
   * @return true si aucune boite de collision est au dessus du point de spawn de l'ennemi, false sinon
   */
  [[nodiscard]] bool isFree() const;

  /**
   * @brief fait apparaitre un ennemi
   * @return pointeur vers l'ennemi créé
   */
  GameObject* spawn();

  /**
   * @brief reset l'horloge interne du spawner.
   */
  void resetClock();

private:
  static inline bool s_registered = ComponentFactory::Register("EnemySpawner", [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
      return std::make_unique<EnemySpawner>(
        node.attribute("ennemyName").as_string()
      );
  });
};


#endif //SIRE_ANNEAU_GAME_ENNEMYSPAWNER_H
