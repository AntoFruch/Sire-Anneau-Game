//
// Created by hugo on 11/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_HEALTHBAR_H
#define COMPONENT_BASED_ARCH_HEALTHBAR_H

#include "Engine.h"
#include "../entities/PlayerController.h" // N'oublie pas l'include
#include "TGUI/Widgets/Panel.hpp"

class HealthBar : public UIDocument {
    tgui::Panel::Ptr backgroundBar;
    tgui::Panel::Ptr foregroundBar;

    // --- Nouveaux attributs pour le Polling ---
    PlayerController* playerTarget{nullptr};
    float lastRatio{-1.0f}; // Initialisé à -1 pour forcer le premier affichage

public:
    HealthBar() = default;
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    void setHealthRatio(float ratio);
};

#endif //COMPONENT_BASED_ARCH_HEALTHBAR_H
