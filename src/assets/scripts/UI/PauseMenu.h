//
// Created by Antonin Fruchet on 09/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_PAUSEMENU_H
#define COMPONENT_BASED_ARCH_PAUSEMENU_H


#include "Engine.h"

class PauseMenu : public UIDocument {
    InputAction* pauseAction;
    bool hidden;

public:
    PauseMenu()=default;
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

private:
    void createResumeButton();
    void createQuitButton();
    void createBackGround();

    void hide();
    void show();
};



#endif //COMPONENT_BASED_ARCH_PAUSEMENU_H
