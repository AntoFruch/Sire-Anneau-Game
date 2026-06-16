//
// Created by Antonin Fruchet on 16/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_BOSSHEALTHBAR_H
#define COMPONENT_BASED_ARCH_BOSSHEALTHBAR_H


#include "Engine.h"
#include "scripts/entities/BossController.h"

#include "TGUI/AllWidgets.hpp"

std::unique_ptr<Component> create_boss_health_bar(pugi::xml_node const& node);

class BossHealthBar : public UIDocument
{
    tgui::Panel::Ptr foregroundBar;
    BossController* target{nullptr};
    float lastRatio{-1.0f}; // Initialisé à -1 pour forcer le premier affichage

public:
    BossHealthBar();
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

private:
    void setHealthRatio(float ratio);

    static inline bool s_registered = ComponentFactory::Register("BossHealthBar", create_boss_health_bar);
};

inline std::unique_ptr<Component> create_boss_health_bar(pugi::xml_node const& node)
{
    return std::make_unique<BossHealthBar>();
}


#endif //COMPONENT_BASED_ARCH_BOSSHEALTHBAR_H
