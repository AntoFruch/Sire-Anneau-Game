//
// Created by Antonin Fruchet on 05/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_CONTROLLER_H
#define COMPONENT_BASED_ARCH_CONTROLLER_H
#include "Engine.h"
#include "Managers/Scene/ComponentFactory.h"
#include "EntityController.h"

std::unique_ptr<Component> create_player_controller(pugi::xml_node const& node);

class PlayerController : public EntityController {
    InputAction* moveAction;
    InputAction* attackAction;
public:
    PlayerController(float speed, int max_hp, int strength);
    ~PlayerController();
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    void takeDamage(int amount) override;

private:
    void attack() override;

    static inline bool s_registered = ComponentFactory::Register("PlayerController", create_player_controller);
};

inline std::unique_ptr<Component> create_player_controller(pugi::xml_node const& node)
{
    return std::make_unique<PlayerController>(
        node.attribute("speed").as_float(),
        node.attribute("max_hp").as_int(),
        node.attribute("strength").as_int()
    );
}



#endif //COMPONENT_BASED_ARCH_CONTROLLER_H
