//
// Created by Antonin Fruchet on 16/06/2026.
//

#include "BossHealthBar.h"

BossHealthBar::BossHealthBar()
{
}

void BossHealthBar::Start()
{
    UIDocument::Start();
    target = gameObject->getComponent<BossController>();

    // 1. Barre de fond configurée en % (15% de la largeur, 2.5% de la hauteur de l'écran)
    auto backgroundBar = tgui::Panel::create();
    backgroundBar->setSize("80%", "3%");
    backgroundBar->setPosition("50% - width/2", "90%");
    backgroundBar->getRenderer()->setBackgroundColor(sf::Color(60, 60, 60)); // Fond gris si vide
    backgroundBar->getRenderer()->setBorders(3); // Bordure épaisse gérée par TGUI
    backgroundBar->getRenderer()->setBorderColor(sf::Color::Black);
    addElement(backgroundBar, "Boss_HP_Background");

    auto bossName = tgui::Label::create(std::string{gameObject->getLabel()});
    bossName->setTextSize(25);
    bossName->getRenderer()->setFont(customFont);
    bossName->setPosition("Boss_HP_Background.left", "Boss_HP_Background.top - height - 4");
    bossName->getRenderer()->setTextColor(sf::Color::White);
    addElement(bossName, "Boss_HP_Name");

    // 2. Jauge rouge : copie conforme du fond via le système de chaînes de TGUI
    // On applique un décalage de 3px pour s'insérer parfaitement à l'intérieur de la bordure
    foregroundBar = tgui::Panel::create();
    foregroundBar->setPosition("Boss_HP_Background.left + 3", "Boss_HP_Background.top + 3");
    foregroundBar->setSize("Boss_HP_Background.width - 6", "Boss_HP_Background.height - 6");
    foregroundBar->getRenderer()->setBackgroundColor(sf::Color::Red);
    addElement(foregroundBar, "Boss_HP_Foreground");
}
void BossHealthBar::Update(const sf::Time& elapsedTime)
{
    UIDocument::Update(elapsedTime);
    if (target) { setHealthRatio(target->getHealthRatio()); }
}

void BossHealthBar::setHealthRatio(float ratio)
{
    // --- 1. GUARD CLAUSE (Le Dirty Flag) ---
    // Si rien n'a changé, on coupe immédiatement l'exécution de la fonction
    if (ratio == lastRatio) return;

    // On mémorise la nouvelle valeur pour la prochaine frame
    lastRatio = ratio;

    // --- 2. SÉCURITÉ ---
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > 1.0f) ratio = 1.0f;

    // --- 3. AFFICHAGE TGUI ---
    foregroundBar->setSize(
        ("(Boss_HP_Background.width - 6) * " + std::to_string(ratio)).c_str(), "Boss_HP_Background.height - 6");

    if (ratio < 0.3f) {
        foregroundBar->getRenderer()->setBackgroundColor(sf::Color(200, 0, 0));
    } else {
        foregroundBar->getRenderer()->setBackgroundColor(sf::Color::Red);
    }
}
