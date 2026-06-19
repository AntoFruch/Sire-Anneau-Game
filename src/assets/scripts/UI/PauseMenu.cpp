//
// Created by Antonin Fruchet on 09/06/2026.
//

#include "PauseMenu.h"

#include "Managers/Input/InputManager.h"
#include "TGUI/Widgets/Button.hpp"
#include "TGUI/Widgets/Panel.hpp"
#include "TGUI/Widgets/Picture.hpp"

void PauseMenu::Start()
{
    UIDocument::Start();
    pauseAction=InputManager::findAction("Pause");

    createBackGround();
    createResumeButton();
    createQuitButton();
    createTitle();

    hide();
}
void PauseMenu::Update(const sf::Time& elapsedTime)
{
    UIDocument::Update(elapsedTime);
    if (pauseAction->wasPerformedThisFrame())
    {
        if (hidden)
        {
            show();
            SceneManager::freeze();
        } else
        {
            hide();
            SceneManager::unfreeze();
        }
    }
}

void PauseMenu::createResumeButton()
{
    auto resumeButton = tgui::Button::create();
    resumeButton->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
    resumeButton->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
    resumeButton->getRenderer()->setBackgroundColorFocused(tgui::Color::Transparent);
    resumeButton->getRenderer()->setBorderColorHover(tgui::Color::Transparent);
    resumeButton->getRenderer()->setBorderColorDown(tgui::Color::Transparent);
    resumeButton->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
    resumeButton->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    resumeButton->getRenderer()->setBorderColor(tgui::Color::Transparent);
    resumeButton->getRenderer()->setBorders(0);

    resumeButton->getRenderer()->setTexture("resources/UI/MainMenu/MenuButton.png");
    resumeButton->setSize(48*8, 16*8);
    resumeButton->setPosition("50% - width*0.5", "50%");

    resumeButton->getRenderer()->setFont(customFont);

    resumeButton->setText("Resume");
    resumeButton->setTextSize(40);

    resumeButton->onPress([this]() {
        hide();
    });
    resumeButton->onMouseEnter([resumeButton]() {
        resumeButton->getRenderer()->setTexture("resources/UI/MainMenu/MenuButtonHover.png");
    });
    resumeButton->onMouseLeave([resumeButton]() {
        resumeButton->getRenderer()->setTexture("resources/UI/MainMenu/MenuButton.png");
    });

    addElement(resumeButton,"Resume");
}
void PauseMenu::createQuitButton()
{
    auto quitButton = tgui::Button::create();
    quitButton->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
    quitButton->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
    quitButton->getRenderer()->setBackgroundColorFocused(tgui::Color::Transparent);
    quitButton->getRenderer()->setBorderColorHover(tgui::Color::Transparent);
    quitButton->getRenderer()->setBorderColorDown(tgui::Color::Transparent);
    quitButton->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
    quitButton->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    quitButton->getRenderer()->setBorderColor(tgui::Color::Transparent);
    quitButton->getRenderer()->setBorders(0);

    quitButton->getRenderer()->setTexture("resources/UI/MainMenu/MenuButton.png");
    quitButton->setSize(48*8, 16*8);
    quitButton->setPosition("50% - width*0.5", "70%");

    quitButton->getRenderer()->setFont(customFont);

    quitButton->setText("Quit");
    quitButton->setTextSize(40);

    quitButton->onPress([this]() {
        SceneManager::requestLoading("resources/scenes/main_menu.xml");
    });
    quitButton->onMouseEnter([quitButton]() {
        quitButton->getRenderer()->setTexture("resources/UI/MainMenu/MenuButtonHover.png");
    });
    quitButton->onMouseLeave([quitButton]() {
        quitButton->getRenderer()->setTexture("resources/UI/MainMenu/MenuButton.png");
    });

    addElement(quitButton,"Quit");
}
void PauseMenu::createBackGround()
{
    auto bg = tgui::Panel::create();
    bg->setSize("100%", "100%");
    bg->setPosition(0,0);
    bg->getRenderer()->setBackgroundColor(sf::Color::Black);
    bg->getRenderer()->setOpacity(0.75);
    addElement(bg,"Background");

    auto overlay = tgui::Picture::create("resources/UI/MainMenu/FondMenuOverlaySimple.png");
    overlay->setSize("100%", "100%");
    overlay->setPosition(0,0);
    addElement(overlay, "OverLay");

}
void PauseMenu::createTitle()
{
    auto title = tgui::Picture::create("resources/UI/Pause.png");
    title->setSize(78*8,21*8);
    title->setPosition("50% - width*0.5", "15%");
    addElement(title, "Title");
}
