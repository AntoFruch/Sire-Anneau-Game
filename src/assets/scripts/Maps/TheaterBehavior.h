//
// Created by Antonin Fruchet on 17/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_THEATERCOMPONENT_H
#define COMPONENT_BASED_ARCH_THEATERCOMPONENT_H


#include "Engine.h"

class TheaterBehavior : public Component
{
public:
    TheaterBehavior() = default;
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

private:
    static inline bool s_registered = ComponentFactory::Register("TheaterBehavior",
                                                                 [](const pugi::xml_node& node) -> std::unique_ptr<
                                                                 Component>
                                                                 {
                                                                     return std::make_unique<TheaterBehavior>();
                                                                 });
};


#endif //COMPONENT_BASED_ARCH_THEATERCOMPONENT_H
