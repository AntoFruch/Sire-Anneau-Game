//
// Created by Antonin Fruchet on 08/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_MAINMENU_H
#define COMPONENT_BASED_ARCH_MAINMENU_H


#include "Engine.h"
#include "Managers/Scene/ComponentFactory.h"

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

    static inline bool s_registered = ComponentFactory::Register("MainMenu", [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
        return std::make_unique<MainMenu>();
    });
};



#endif //COMPONENT_BASED_ARCH_MAINMENU_H
