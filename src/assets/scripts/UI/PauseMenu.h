//
// Created by Antonin Fruchet on 09/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_PAUSEMENU_H
#define COMPONENT_BASED_ARCH_PAUSEMENU_H


#include "Engine.h"
#include "Managers/Scene/ComponentFactory.h"

std::unique_ptr<Component> create_pause_menu(pugi::xml_node const& node);

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
    void createTitle();

    void hide();
    void show();

    static inline bool s_registered = ComponentFactory::Register("PauseMenu", create_pause_menu);
};

inline std::unique_ptr<Component> create_pause_menu(pugi::xml_node const& node)
{
    return std::make_unique<PauseMenu>();
}



#endif //COMPONENT_BASED_ARCH_PAUSEMENU_H
