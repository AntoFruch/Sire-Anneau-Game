//
// Created by Antonin Fruchet on 08/06/2026.
//

#include "MainMenuUI.h"
#include <cstdlib>
#include <cmath>

#include "TGUI/Widgets/Button.hpp"

// --- ENREGISTREMENT AUTOMATIQUE ---
// On crée une variable globale/statique anonyme.
// Son seul but est de s'exécuter AVANT le début du jeu pour enregistrer le composant.
namespace {
    const bool registered = []() {
        ComponentFactory::Register("MainMenuUI", [](const pugi::xml_node& node) {
            return std::make_unique<MainMenuUI>();
        });
        return true;
    }();
}
// --------------------------

// ─── Constants ───────────────────────────────────────────────────────────────
static constexpr float PARTICLE_COUNT   = 12;
static constexpr float PARTICLE_SPEED   = 60.f;   // px/s upward
static constexpr float PARTICLE_FADE_IN = 0.15f;  // fraction of lifetime

// ─── Start ───────────────────────────────────────────────────────────────────
void MainMenuUI::Start()
{
    Component::Start();
    gui = SceneManager::getGui();

    // ── Background ────────────────────────────────────────────────────────────
    auto bg = tgui::Picture::create("resources/UI/MainMenu/background.png");
    bg->setSize("100%", "100%");
    bg->setPosition(0, 0);
    gui->add(bg, "BgImage");

    // ── Title ─────────────────────────────────────────────────────────────────
    auto subtitle = tgui::Label::create();
    subtitle->setText("The Legend of");
    subtitle->setPosition("50%", "18%");
    subtitle->setOrigin(0.5f, 0.5f);
    subtitle->getRenderer()->setTextColor(tgui::Color(201, 168, 76));
    subtitle->setTextSize(50);
    gui->add(subtitle, "Subtitle");

    auto title = tgui::Label::create();
    title->setText("Sire Anneau");
    title->setPosition("50%", "33%");
    title->setOrigin(0.5f, 0.5f);
    title->getRenderer()->setTextColor(tgui::Color(240, 223, 160));
    title->setTextSize(135);
    gui->add(title, "Title");

    // ── Ornament ──────────────────────────────────────────────────────────────
    auto orn = tgui::Picture::create("resources/UI/MainMenu/ornament.png");
    orn->setSize(320, 20);
    orn->setPosition("50%", "50%");
    orn->setOrigin(0.5f, 0.5f);
    gui->add(orn, "Ornament");

    // ── Bouton Jouer ─────────────────────────────────────────────────────────
    auto btnJouer = tgui::BitmapButton::create();
    btnJouer->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
    btnJouer->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
    btnJouer->getRenderer()->setBackgroundColorFocused(tgui::Color::Transparent);
    btnJouer->getRenderer()->setBorderColorHover(tgui::Color::Transparent);
    btnJouer->getRenderer()->setBorderColorDown(tgui::Color::Transparent);
    btnJouer->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
    btnJouer->getRenderer()->setTextColorHover(tgui::Color(201, 168, 76));
    btnJouer->setImage("resources/UI/MainMenu/button_play.png");
    btnJouer->setImageScaling(1.f);
    btnJouer->setSize(400, 70);
    btnJouer->setPosition("50%", "52%");
    btnJouer->setOrigin(0.5f, 0.5f);
    btnJouer->setText("JOUER");
    btnJouer->setTextSize(16);
    btnJouer->getRenderer()->setTextColor(tgui::Color(201, 168, 76));
    btnJouer->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    btnJouer->getRenderer()->setBorderColor(tgui::Color::Transparent);
    btnJouer->getRenderer()->setBorders(0);
    btnJouer->onPress([this]() {
        SceneManager::requestLoading("resources/scenes/scene.xml");
    });
    btnJouer->onMouseEnter([btnJouer]() {
        btnJouer->setImage("resources/UI/MainMenu/button_play_hover.png");
    });
    btnJouer->onMouseLeave([btnJouer]() {
        btnJouer->setImage("resources/UI/MainMenu/button_play.png");
    });
    gui->add(btnJouer, "BtnJouer");

    // ── Bouton Quitter ────────────────────────────────────────────────────────
    auto btnQuitter = tgui::BitmapButton::create();
    btnQuitter->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
    btnQuitter->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
    btnQuitter->getRenderer()->setBackgroundColorFocused(tgui::Color::Transparent);
    btnQuitter->getRenderer()->setBorderColorHover(tgui::Color::Transparent);
    btnQuitter->getRenderer()->setBorderColorDown(tgui::Color::Transparent);
    btnQuitter->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
    btnQuitter->getRenderer()->setTextColorHover(tgui::Color(201, 168, 76));
    btnQuitter->setImage("resources/UI/MainMenu/button_play.png");
    btnQuitter->setSize(400, 70);
    btnQuitter->setPosition("50%", "64%");
    btnQuitter->setOrigin(0.5f, 0.5f);
    btnQuitter->setText("QUITTER");
    btnQuitter->setTextSize(16);
    btnQuitter->getRenderer()->setTextColor(tgui::Color(201, 168, 76));
    btnQuitter->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    btnQuitter->getRenderer()->setBorderColor(tgui::Color::Transparent);
    btnQuitter->getRenderer()->setBorders(0);
    btnQuitter->onPress([]() {
        std::exit(0);
    });
    btnQuitter->onMouseEnter([btnQuitter]() {
        btnQuitter->setImage("resources/UI/MainMenu/button_play_hover.png");
    });
    btnQuitter->onMouseLeave([btnQuitter]() {
        btnQuitter->setImage("resources/UI/MainMenu/button_play.png");
    });
    gui->add(btnQuitter, "BtnQuitter");

    // ── Version label ─────────────────────────────────────────────────────────
    auto version = tgui::Label::create();
    version->setText("v1.0.0");
    version->setPosition("98%", "96%");
    version->setOrigin(1.f, 1.f);
    version->setTextSize(11);
    version->getRenderer()->setTextColor(tgui::Color(201, 168, 76, 60));
    gui->add(version, "Version");

    // ── Particules ────────────────────────────────────────────────────────────
    initParticles();
}

// ─── initParticles ────────────────────────────────────────────────────────────
void MainMenuUI::initParticles()
{
    particles.clear();
    static const float xPositions[] = {
        0.18f, 0.28f, 0.38f, 0.48f, 0.52f, 0.58f,
        0.64f, 0.70f, 0.76f, 0.35f, 0.55f, 0.42f
    };

    for (int i = 0; i < static_cast<int>(PARTICLE_COUNT); ++i)
    {
        Particle p;
        p.widget = tgui::Picture::create("resources/UI/MainMenu/particle.png");
        p.widget->setSize(8, 8);
        p.widget->setOrigin(0.5f, 0.5f);

        p.xPercent  = xPositions[i % 12];
        p.lifetime  = 7.f + (i % 5) * 1.2f;
        p.elapsed   = static_cast<float>(i % static_cast<int>(p.lifetime));
        p.alpha     = 0.f;

        gui->add(p.widget);
        particles.push_back(std::move(p));
    }
}

// ─── Update ───────────────────────────────────────────────────────────────────
void MainMenuUI::Update(const sf::Time& elapsedTime)
{
    Component::Update(elapsedTime);

    // Title pulse (sine on opacity/color brightness)
    titleTimer += elapsedTime.asSeconds();
    if (auto titleW = gui->get<tgui::Label>("Title"))
    {
        float pulse = 0.85f + 0.15f * std::sin(titleTimer * 1.4f);
        int   v     = static_cast<int>(223 * pulse);
        int   vr    = static_cast<int>(240 * pulse);
        titleW->getRenderer()->setTextColor(tgui::Color(vr, v, 140));
    }

    // Particles float upward
    auto winSize = gui->getView().getSize();
    float wW = winSize.x;
    float wH = winSize.y;

    for (auto& p : particles)
    {
        p.elapsed += elapsedTime.asSeconds();
        if (p.elapsed >= p.lifetime)
            p.elapsed -= p.lifetime;

        float progress = p.elapsed / p.lifetime;   // 0→1

        // Fade in then out
        float fade;
        if (progress < PARTICLE_FADE_IN)
            fade = progress / PARTICLE_FADE_IN;
        else if (progress > 0.85f)
            fade = (1.f - progress) / 0.15f;
        else
            fade = 1.f;

        p.alpha = fade;
        p.widget->setInheritedOpacity(p.alpha * 0.75f);

        // Y: starts at 90% screen, moves upward
        float yBase   = wH * 0.90f;
        float yTravel = wH * 0.55f;
        float yPos    = yBase - progress * yTravel;

        p.widget->setPosition(p.xPercent * wW, yPos);
    }
}
MainMenuUI::~MainMenuUI()
{
    gui->removeAllWidgets();
}


