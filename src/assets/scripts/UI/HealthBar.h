//
// Created by Antonin Fruchet on 07/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_UITEXTBOX_H
#define COMPONENT_BASED_ARCH_UITEXTBOX_H
#include "Engine.h"

class HealthBar : public UIElement {
  sf::RectangleShape container;

public:
  HealthBar();
  void Start() override;
  void Update(const sf::Time &elapsedTime) override;
  void draw(sf::RenderWindow& window) override;
};



#endif //COMPONENT_BASED_ARCH_UITEXTBOX_H
