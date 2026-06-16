//
// Created by Antonin Fruchet on 08/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_MAINMENU_H
#define COMPONENT_BASED_ARCH_MAINMENU_H


#include "Engine.h"
#include "Managers/Scene/ComponentFactory.h"

std::unique_ptr<Component> create_main_menu(pugi::xml_node const& node);

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

    static inline bool s_registered = ComponentFactory::Register("MainMenu", create_main_menu);
};

inline std::unique_ptr<Component> create_main_menu(pugi::xml_node const& node)
{
    return std::make_unique<MainMenu>();
}



#endif //COMPONENT_BASED_ARCH_MAINMENU_H
