//
// Created by Antonin Fruchet on 10/06/2026.
//

#include "LoadingZone.h"

#include "LoadingZoneManager.h"
#include "scripts/entities/PlayerController.h"

// --- ENREGISTREMENT AUTOMATIQUE ---
// On crée une variable globale/statique anonyme.
// Son seul but est de s'exécuter AVANT le début du jeu pour enregistrer le composant.
namespace {
    const bool registered = []() {
        ComponentFactory::Register("LoadingZone", [](const pugi::xml_node& node)
        {
            return std::make_unique<LoadingZone>(
                node.attribute("sceneToLoad").as_string(),
                node.attribute("doorId").as_uint(),
                node.attribute("targetDoorId").as_uint(),
                node.attribute("spawnX").as_float(),
                node.attribute("spawnY").as_float()
            );
        });
        return true;
    }();
}
// --------------------------

LoadingZone::LoadingZone(const std::string& sceneToLoad, unsigned int doorId, unsigned int targetDoorId, float spawnX, float spawnY)
    : sceneToLoad(sceneToLoad), doorId(doorId), targetDoorId(targetDoorId), spawnPoint(sf::Vector2f(spawnX, spawnY))
{
}

void LoadingZone::Start()
{
    Component::Start();
    LoadingZoneManager::registerLZ(this);
    spawnPoint += gameObject->transform.getWorldPosition();
    gameObject->getComponent<Collider>()->setTriggerCallback(
        [this](const std::vector<Collider*>& hits, Collider* trigger)
        {
            for (const auto& hit  : hits)
            {
                if (hit->gameObject->getComponent<PlayerController>())
                    LoadingZoneManager::requestLoading(sceneToLoad, targetDoorId);
            }
        });
}
void LoadingZone::Update(const sf::Time& elapsedTime)
{
    Component::Update(elapsedTime);
}

unsigned int LoadingZone::getDoorID()
{
    return doorId;
}

const sf::Vector2f& LoadingZone::getSpawnPoint() const
{
    return spawnPoint;
}
