//
// Created by Antonin Fruchet on 11/06/2026.
//

#include "EnemyController.h"

// --- ENREGISTREMENT AUTOMATIQUE ---
// On crée une variable globale/statique anonyme.
// Son seul but est de s'exécuter AVANT le début du jeu pour enregistrer le composant.
namespace {
    const bool registered = []() {
        ComponentFactory::Register("EnemyController", [](const pugi::xml_node& node) {
            return std::make_unique<EnemyController>(
                sf::Vector2f{
                    node.attribute("colliderX").as_float(),
                    node.attribute("colliderY").as_float()
                },
                sf::Vector2f{
                    node.attribute("colliderW").as_float(),
                    node.attribute("colliderH").as_float()
                },
                node.attribute("speed").as_float(),
                node.attribute("max_hp").as_int(),
                node.attribute("strength").as_int()
                );
        });
        return true;
    }();
}
// --------------------------

EnemyController::EnemyController(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize, float speed, int max_hp, int strength)
    : EntityController(colliderPos, colliderSize, speed, max_hp, strength)
{
}

void EnemyController::Start()
{
    EntityController::Start();
}
void EnemyController::Update(const sf::Time& elapsedTime)
{
    EntityController::Update(elapsedTime);
}

void EnemyController::takeDamage(int amount)
{
    EntityController::takeDamage(amount);
}