//
// Created by Antonin Fruchet on 17/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_GAMEOVERMENU_H
#define COMPONENT_BASED_ARCH_GAMEOVERMENU_H


#include "Engine.h"
#include "Managers/Scene/ComponentFactory.h"

class GameOverMenu : public UIDocument {
    bool hidden;

public:
    GameOverMenu()=default;
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

private:
    void createRetryButton();
    void createQuitButton();
    void createBackGround();
    void createTitle();

    void hide();
    void show();

    static inline bool s_registered = ComponentFactory::Register("GameOverMenu", [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
        return std::make_unique<GameOverMenu>();
    });
};



#endif //COMPONENT_BASED_ARCH_GAMEOVERMENU_H
