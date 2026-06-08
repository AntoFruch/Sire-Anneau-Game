//
// Created by Antonin Fruchet on 08/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_MAINMENUUI_H
#define COMPONENT_BASED_ARCH_MAINMENUUI_H


#include "Engine.h"
#include <TGUI/AllWidgets.hpp>

class MainMenuUI : public Component {
    tgui::Gui* gui{nullptr};

    // ── Particle ──────────────────────────────────────────────────────────────
    struct Particle {
        tgui::Picture::Ptr widget;
        float xPercent  = 0.5f;   // horizontal position [0,1]
        float lifetime  = 8.f;    // seconds for full cycle
        float elapsed   = 0.f;    // current time in cycle
        float alpha     = 0.f;
    };

    float titleTimer = 0.f;
    std::vector<Particle> particles;

    void initParticles();

public:
    MainMenuUI() = default;
    ~MainMenuUI();
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;
};



#endif //COMPONENT_BASED_ARCH_MAINMENUUI_H
