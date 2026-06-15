//
// Created by hugo on 11/06/2026.
//

#include "HealthBar.h"

#include "scripts/entities/PlayerController.h"
#include "scripts/GameManager.h"
#include "TGUI/Widgets/Panel.hpp"

void HealthBar::Start()
{
    UIDocument::Start();

    // 1. Barre de fond configurée en % (15% de la largeur, 2.5% de la hauteur de l'écran)
    backgroundBar = tgui::Panel::create();
    backgroundBar->setSize("15%", "2.5%");
    backgroundBar->setPosition("2%", "2%"); // Placé à 2% des bords haut/gauche
    backgroundBar->getRenderer()->setBackgroundColor(sf::Color(60, 60, 60)); // Fond gris si vide
    backgroundBar->getRenderer()->setBorders(3); // Bordure épaisse gérée par TGUI
    backgroundBar->getRenderer()->setBorderColor(sf::Color::Black);
    addElement(backgroundBar, "HP_Background");

    // 2. Jauge rouge : copie conforme du fond via le système de chaînes de TGUI
    // On applique un décalage de 3px pour s'insérer parfaitement à l'intérieur de la bordure
    foregroundBar = tgui::Panel::create();
    foregroundBar->setPosition("HP_Background.left + 3", "HP_Background.top + 3");
    foregroundBar->setSize("HP_Background.width - 6", "HP_Background.height - 6");
    foregroundBar->getRenderer()->setBackgroundColor(sf::Color::Red);
    addElement(foregroundBar, "HP_Foreground");
}

void HealthBar::Update(const sf::Time& elapsedTime)
{
    UIDocument::Update(elapsedTime);
    if (PlayerController* playerTarget = GameManager::getPlayer()) { setHealthRatio(playerTarget->getHealthRatio()); }
}

void HealthBar::setHealthRatio(float ratio)
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
        ("(HP_Background.width - 6) * " + std::to_string(ratio)).c_str(), "HP_Background.height - 6");

    if (ratio < 0.3f) {
        foregroundBar->getRenderer()->setBackgroundColor(sf::Color(200, 0, 0));
    } else {
        foregroundBar->getRenderer()->setBackgroundColor(sf::Color::Red);
    }
}
