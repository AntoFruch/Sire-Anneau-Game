//
// Created by Antonin Fruchet on 19/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_TEXTBOX_H
#define COMPONENT_BASED_ARCH_TEXTBOX_H


#include "Engine.h"
#include "TGUI/Widgets/Label.hpp"

class TextBox : public UIDocument {
    InputAction* nextAction{nullptr};

    std::vector<std::string> buffer;
    int currentIndex{0};

    tgui::Label::Ptr text;
public:
    TextBox()=default;
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;
    void open();
    void next();

    void setBuffer(const std::vector<std::string>& buffer);

private:
    static inline bool s_registered = ComponentFactory::Register("TextBox", 
        [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
            return std::make_unique<TextBox>();
        });
};



#endif //COMPONENT_BASED_ARCH_TEXTBOX_H
