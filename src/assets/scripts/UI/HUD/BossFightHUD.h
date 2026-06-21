//
// Created by Antonin Fruchet on 21/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_BOSSFIGHTHUD_H
#define COMPONENT_BASED_ARCH_BOSSFIGHTHUD_H


#include "Engine.h"
#include "TGUI/Widgets/Label.hpp"

class BossFightController;

class BossFightHUD : public UIDocument {
    tgui::Label::Ptr text;
public:
    BossFightHUD()=default;
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;
private:
    static inline bool s_registered = ComponentFactory::Register("BossFightHUD", 
        [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
            return std::make_unique<BossFightHUD>();
        });
};



#endif //COMPONENT_BASED_ARCH_BOSSFIGHTHUD_H
