//
// Created by Antonin Fruchet on 17/06/2026.
//

#include "GameOverMenu.h"

#include "scripts/GameManager.h"
#include "TGUI/Widgets/Button.hpp"
#include "TGUI/Widgets/Panel.hpp"
#include "TGUI/Widgets/Picture.hpp"

void GameOverMenu::Start()
{
    UIDocument::Start();

    createBackGround();
    createRetryButton();
    createQuitButton();
    createTitle();

    hide();
    SceneManager::unfreeze();
}

void GameOverMenu::Update(const sf::Time& elapsedTime)
{
    UIDocument::Update(elapsedTime);
    if (hidden)
    {
        if (PlayerController* player = GameManager::getPlayer(); player && player->isGameOver())
        {
            show();
            moveToFront();
            SceneManager::freeze();
        }
    }
}

void GameOverMenu::createRetryButton()
{
    auto retryButton = tgui::Button::create();
    retryButton->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
    retryButton->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
    retryButton->getRenderer()->setBackgroundColorFocused(tgui::Color::Transparent);
    retryButton->getRenderer()->setBorderColorHover(tgui::Color::Transparent);
    retryButton->getRenderer()->setBorderColorDown(tgui::Color::Transparent);
    retryButton->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
    retryButton->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    retryButton->getRenderer()->setBorderColor(tgui::Color::Transparent);
    retryButton->getRenderer()->setBorders(0);

    retryButton->getRenderer()->setTexture("resources/UI/MainMenu/MenuButton.png");
    retryButton->setSize(48*8, 16*8);
    retryButton->setPosition("50% - width*0.5", "50%");

    retryButton->getRenderer()->setFont(customFont);

    retryButton->setText("Retry");
    retryButton->setTextSize(40);

    retryButton->onPress([this]() {
        SceneManager::requestLoading("resources/scenes/outside.xml");
    });
    retryButton->onMouseEnter([retryButton]() {
        retryButton->getRenderer()->setTexture("resources/UI/MainMenu/MenuButtonHover.png");
    });
    retryButton->onMouseLeave([retryButton]() {
        retryButton->getRenderer()->setTexture("resources/UI/MainMenu/MenuButton.png");
    });

    addElement(retryButton,"Retry");
}

void GameOverMenu::createQuitButton()
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

    addElement(quitButton,"GO_Quit");
}

void GameOverMenu::createBackGround()
{
    auto bg = tgui::Panel::create();
    bg->setSize("100%", "100%");
    bg->setPosition(0,0);
    bg->getRenderer()->setBackgroundColor(sf::Color::Black);
    bg->getRenderer()->setOpacity(0.75);
    addElement(bg,"GO_Background");

    auto overlay = tgui::Picture::create("resources/UI/MainMenu/FondMenuOverlaySimple.png");
    overlay->setSize("100%", "100%");
    overlay->setPosition(0,0);
    addElement(overlay, "GO_OverLay");
}

void GameOverMenu::createTitle()
{
    auto title = tgui::Picture::create("resources/UI/GameOver.png");
    title->setSize(142*8,21*8);
    title->setPosition("50% - width*0.5", "15%");
    addElement(title, "GO_Title");
}


