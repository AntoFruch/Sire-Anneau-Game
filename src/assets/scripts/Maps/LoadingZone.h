//
// Created by Antonin Fruchet on 10/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_LOADINGZONE_H
#define COMPONENT_BASED_ARCH_LOADINGZONE_H


#include "Engine.h"
#include "Managers/Scene/ComponentFactory.h"

/**
 * @brief Composant permettant de creer des zones de chargement de scenes, en mappant les zones portes à portes (LoadingZone à LoadingZone).
 */
class LoadingZone : public Component
{
    const std::string sceneToLoad;      // chemin de la scene à charger
    const unsigned int doorId;          // id de cette loadingZone
    const unsigned int targetDoorId;    // id de la loadingZone d'arrivée dans la prochaine scène

    sf::Vector2f spawnPoint;            // offset par rapport a la position de la loading zone pour placer le joueur devant

public:
    LoadingZone(const std::string& sceneToLoad, unsigned int doorId, unsigned int targetDoorId, float spawnX, float spawnY);
    ~LoadingZone();
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    unsigned int getDoorID();
    const sf::Vector2f& getSpawnPoint() const;

private:
    static inline bool s_registered = ComponentFactory::Register("LoadingZone", [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
        return std::make_unique<LoadingZone>(
            node.attribute("sceneToLoad").as_string(),
            node.attribute("doorId").as_uint(),
            node.attribute("targetDoorId").as_uint(),
            node.attribute("spawnX").as_float(),
            node.attribute("spawnY").as_float()
        );
    });
};


#endif //COMPONENT_BASED_ARCH_LOADINGZONE_H
