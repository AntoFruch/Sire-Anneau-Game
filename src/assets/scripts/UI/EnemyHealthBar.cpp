//
// Created by Antonin Fruchet on 19/06/2026.
//

#include "EnemyHealthBar.h"

void EnemyHealthBar::Start()
{
    UIDocument::Start();

    target = gameObject->getComponent<EnemyController>();

    backgroundBar = tgui::Panel::create();
    backgroundBar->setSize("5%", "1%");
    backgroundBar->getRenderer()->setBackgroundColor(sf::Color(60, 60, 60)); // Fond gris si vide
    addElement(backgroundBar, "Enemy_HP_Background");

    foregroundBar = tgui::Panel::create();
    foregroundBar->getRenderer()->setBackgroundColor(sf::Color::Red);
    addElement(foregroundBar, "Enemy_HP_Foreground");

    show();
}
void EnemyHealthBar::Update(const sf::Time& elapsedTime)
{
    UIDocument::Update(elapsedTime);
    auto windowPos = RenderManager::getWindow()->mapCoordsToPixel(gameObject->transform.getWorldPosition());
    auto barPos = sf::Vector2f{
        windowPos.x - gameObject->getComponent<Renderer>()->getSpriteSize().x/2 * gameObject->transform.getWorldScale().x,
        windowPos.y - gameObject->getComponent<Renderer>()->getSpriteSize().y * gameObject->transform.getWorldScale().y
        };
    backgroundBar->setPosition(barPos.x, barPos.y);
    foregroundBar->setPosition(barPos.x, barPos.y);

    if (target) setHealthRatio(target->getHealthRatio());
}

void EnemyHealthBar::setHealthRatio(float ratio)
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
        ("(Enemy_HP_Background.width) * " + std::to_string(ratio)).c_str(), "Enemy_HP_Background.height");

    if (ratio < 0.3f) {
        foregroundBar->getRenderer()->setBackgroundColor(sf::Color(200, 0, 0));
    } else {
        foregroundBar->getRenderer()->setBackgroundColor(sf::Color::Red);
    }
}


