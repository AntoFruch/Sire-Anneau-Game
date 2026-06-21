//
// Created by Antonin Fruchet on 21/06/2026.
//

#include "BossFightHUD.h"

#include "scripts/Maps/BossFightController.h"
#include "TGUI/Widgets/Picture.hpp"


void BossFightHUD::Start()
{
    UIDocument::Start();

    auto bg = tgui::Picture::create("resources/UI/textbox.png");
    bg->setPosition("50% - width/2", "2%");
    bg->setSize("42%", "14%");
    addElement(bg, "BossFight_bg");

    text = tgui::Label::create();
    text->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
    text->setVerticalAlignment(tgui::VerticalAlignment::Center);
    text->setPosition("BossFight_bg.left + 24", "BossFight_bg.top + 12");
    text->setSize("BossFight_bg.width - 48", "BossFight_bg.height - 24");
    text->setTextSize(50);
    text->getRenderer()->setFont(customFont);
    text->getRenderer()->setTextColor(sf::Color(60,60,60));

    addElement(text, "BossFight_text");
}
void BossFightHUD::Update(const sf::Time& elapsedTime)
{
    UIDocument::Update(elapsedTime);
    auto* fight = BossFightController::getActiveFight();
    if (fight == nullptr || fight->isCompleted())
    {
        hide();
        return;
    }
    else
    {
        show();
    }

    text->setText(std::format("Enemies killed : {} / {}",
        fight->getKilledEnemies(), fight->getTotalEnemies()));
}

