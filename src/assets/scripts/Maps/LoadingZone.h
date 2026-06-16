//
// Created by Antonin Fruchet on 10/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_LOADINGZONE_H
#define COMPONENT_BASED_ARCH_LOADINGZONE_H


#include "Engine.h"
#include "Managers/Scene/ComponentFactory.h"

std::unique_ptr<Component> create_loading_zone(pugi::xml_node const& node);

class LoadingZone : public Component
{
    const std::string sceneToLoad;
    const unsigned int doorId;
    const unsigned int targetDoorId;

    sf::Vector2f spawnPoint;

public:
    LoadingZone(const std::string& sceneToLoad, unsigned int doorId, unsigned int targetDoorId, float spawnX, float spawnY);
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    unsigned int getDoorID();
    const sf::Vector2f& getSpawnPoint() const;

private:
    static inline bool s_registered = ComponentFactory::Register("LoadingZone", create_loading_zone);
};

inline std::unique_ptr<Component> create_loading_zone(pugi::xml_node const& node)
{
    return std::make_unique<LoadingZone>(
        node.attribute("sceneToLoad").as_string(),
        node.attribute("doorId").as_uint(),
        node.attribute("targetDoorId").as_uint(),
        node.attribute("spawnX").as_float(),
        node.attribute("spawnY").as_float()
    );
}


#endif //COMPONENT_BASED_ARCH_LOADINGZONE_H
