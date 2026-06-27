//
// Created by Antonin Fruchet on 08/06/2026.
//

#include "MainMenu.h"

#include "scripts/Maps/LoadingZoneManager.h"
#include "TGUI/Widgets/Button.hpp"
#include "TGUI/Widgets/Picture.hpp"

void MainMenu::createPlayButton()
{
    auto playButton = tgui::Button::create();
    playButton->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
    playButton->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
    playButton->getRenderer()->setBackgroundColorFocused(tgui::Color::Transparent);
    playButton->getRenderer()->setBorderColorHover(tgui::Color::Transparent);
    playButton->getRenderer()->setBorderColorDown(tgui::Color::Transparent);
    playButton->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
    playButton->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    playButton->getRenderer()->setBorderColor(tgui::Color::Transparent);
    playButton->getRenderer()->setBorders(0);

    playButton->getRenderer()->setTexture("resources/UI/MainMenu/MenuButton.png");
    playButton->setSize(48*8, 16*8);
    playButton->setPosition("50% - width*0.5", "50%");

    playButton->getRenderer()->setFont(customFont);

    playButton->setText("Play");
    playButton->setTextSize(40);

    playButton->onPress([]() {
        LoadingZoneManager::reset();
        SceneManager::requestLoading("resources/scenes/outside.xml");
    });
    auto playButtonWeak = playButton.get();
    playButton->onMouseEnter([playButtonWeak]() {
        playButtonWeak->getRenderer()->setTexture("resources/UI/MainMenu/MenuButtonHover.png");
    });
    playButton->onMouseLeave([playButtonWeak]() {
        playButtonWeak->getRenderer()->setTexture("resources/UI/MainMenu/MenuButton.png");
    });


    addElement(playButton,"Play");
}

void MainMenu::createQuitButton()
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

    quitButton->onPress([]() {
        RenderManager::closeWindow();
    });
    auto quitButtonWeak = quitButton.get();
    quitButton->onMouseEnter([quitButtonWeak]() {
        quitButtonWeak->getRenderer()->setTexture("resources/UI/MainMenu/MenuButtonHover.png");
    });
    quitButton->onMouseLeave([quitButtonWeak]() {
        quitButtonWeak->getRenderer()->setTexture("resources/UI/MainMenu/MenuButton.png");
    });

    addElement(quitButton,"Quit");
}

void MainMenu::createTitle()
{
    auto title = tgui::Picture::create("resources/UI/MainMenu/Title.png");
    title->setSize(104*8,42*8);
    title->setPosition("50% - width*0.5", "7%");
    addElement(title, "Title");
}

void MainMenu::createBackground()
{
    auto bg = tgui::Picture::create("resources/UI/MainMenu/FondMenu.png");
    bg->getRenderer()->setOpacity(0.3);
    bg->setSize("100%", "100%");
    bg->setPosition(0,0);
    addElement(bg, "Background");
}

void MainMenu::Start()
{
    UIDocument::Start();

    createBackground();
    createTitle();
    createPlayButton();
    createQuitButton();
}


void MainMenu::Update(const sf::Time& elapsedTime)
{
    UIDocument::Update(elapsedTime);
}
