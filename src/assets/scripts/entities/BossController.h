//
// Created by Antonin Fruchet on 16/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_BOSSCONTROLLER_H
#define COMPONENT_BASED_ARCH_BOSSCONTROLLER_H


#include "EnemyController.h"
#include "Engine.h"

class BossController : public EnemyController
{
public:
    BossController(float speed, int max_hp, int strength);
    ~BossController();
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;
    void die();

private:
    static inline bool s_registered =
        ComponentFactory::Register("BossController",
             [](const pugi::xml_node& node) -> std::unique_ptr<Component>
             {
                 return std::make_unique<BossController>(
                    node.attribute("speed").as_float(),
                    node.attribute("max_hp").as_int(),
                    node.attribute("strength").as_int()
                    );
             });
};


#endif //COMPONENT_BASED_ARCH_BOSSCONTROLLER_H
