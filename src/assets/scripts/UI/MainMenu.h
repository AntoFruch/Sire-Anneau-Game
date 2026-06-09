//
// Created by Antonin Fruchet on 08/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_MAINMENU_H
#define COMPONENT_BASED_ARCH_MAINMENU_H


#include "Engine.h"

class MainMenu : public UIDocument {
public:
    MainMenu() = default;
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

private:
    void createPlayButton();
    void createQuitButton();
    void createTitle();
    void createBackground();
};



#endif //COMPONENT_BASED_ARCH_MAINMENU_H
