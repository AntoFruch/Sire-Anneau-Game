//
// Created by Antonin Fruchet on 07/06/2026.
//

#include "HealthBar.h"

// --- ENREGISTREMENT AUTOMATIQUE ---
// On crée une variable globale/statique anonyme.
// Son seul but est de s'exécuter AVANT le début du jeu pour enregistrer le composant.
namespace {
const bool registered = []() {
  ComponentFactory::Register("HealthBar", [](const pugi::xml_node& node) {
      auto ptr = std::make_unique<HealthBar>();
    UIManager::registerUIElement(ptr.get());
    return std::move(ptr);
  });
  return true;
}();
}
// --------------------------

HealthBar::HealthBar() {
}

void HealthBar::Start() {
  UIElement::Start();
  container.setPosition({10, 10});
  container.setSize({100,10});
  container.setOutlineColor(sf::Color{50, 50, 50});
  container.setFillColor(sf::Color::Red);
}
void HealthBar::Update(const sf::Time &elapsedTime) {
  UIElement::Update(elapsedTime);

}
void HealthBar::draw(sf::RenderWindow& window) {
  window.draw(container);
}
