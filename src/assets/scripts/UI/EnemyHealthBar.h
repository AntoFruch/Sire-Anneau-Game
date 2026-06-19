//
// Created by Antonin Fruchet on 19/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_ENEMYHEALTHBAR_H
#define COMPONENT_BASED_ARCH_ENEMYHEALTHBAR_H


#include "Engine.h"
#include "scripts/entities/EnemyController.h"
#include "TGUI/Widgets/Panel.hpp"

class EnemyHealthBar : public UIDocument {
    tgui::Panel::Ptr backgroundBar;
    tgui::Panel::Ptr foregroundBar;

    EnemyController* target;

    float lastRatio{-1.0f}; // Initialisé à -1 pour forcer le premier affichage

public:
    EnemyHealthBar() = default;
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    void setHealthRatio(float ratio);
private:
    static inline bool s_registered = ComponentFactory::Register("EnemyHealthBar", 
        [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
            return std::make_unique<EnemyHealthBar>();
        });
};



#endif //COMPONENT_BASED_ARCH_ENEMYHEALTHBAR_H
