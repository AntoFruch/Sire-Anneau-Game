//
// Created by Antonin Fruchet on 19/06/2026.
//

#include "TextBox.h"

#include "Managers/Input/InputManager.h"
#include "scripts/GameManager.h"
#include "TGUI/Widgets/Label.hpp"
#include "TGUI/Widgets/Picture.hpp"

void TextBox::Start()
{
    UIDocument::Start();
    GameManager::registerTB(this);
    nextAction = InputManager::findAction("TextBoxNext");

    auto bg = tgui::Picture::create("resources/UI/textbox.png");
    bg->setSize("80%", "25%");
    bg->setPosition("10%", "70%");
    addElement(bg, "TB_bg");

    text = tgui::Label::create();
    text->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
    text->setVerticalAlignment(tgui::VerticalAlignment::Center);
    text->setPosition("TB_bg.left + 48", "TB_bg.top + 24");
    text->setSize("TB_bg.width - 96", "TB_bg.height - 48");
    text->setTextSize(50);
    text->getRenderer()->setFont(customFont);
    text->getRenderer()->setTextColor(sf::Color::Black);
    addElement(text, "TB_text");

    hide();
}
void TextBox::Update(const sf::Time& elapsedTime)
{
    UIDocument::Update(elapsedTime);
    if (nextAction && nextAction->wasPerformedThisFrame())
    {
        next();
    }
}

void TextBox::open()
{
    currentIndex = 0;
    if (!buffer.empty())
    {
        text->setText(buffer[currentIndex]);
    }
    show();
}

void TextBox::next()
{
    currentIndex++;
    if (currentIndex >= buffer.size())
    {
        currentIndex=0;
        buffer.clear();
        hide();
        text->setText("");
        return;
    }

    text->setText(buffer[currentIndex]);
}

void TextBox::setBuffer(const std::vector<std::string>& buffer)
{
    this->buffer = buffer;
    currentIndex = 0;
    if (text && !this->buffer.empty())
    {
        text->setText(this->buffer[currentIndex]);
    }
}

