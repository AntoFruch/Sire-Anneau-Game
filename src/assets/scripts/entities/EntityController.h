//
// Created by Antonin Fruchet on 06/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
#define COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
#include "Engine.h"


class EntityController : public CharacterController {
    float speed;

protected:
    sf::Vector2f facing{0,1}; // facing bottom by default

    // Callback called when attacking successfully
    void(*attackCallback)(const std::vector<Collider*>&, Collider*);

public:
    EntityController(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize, float speed);
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    /**
     * @brief Handles the movement of the entity with the speed, from a direction only
     * @param rawDir entity will move toward this direction
     * @param elapsedTime time between last frame and this frame
     */
    void moveEntity(const sf::Vector2f& rawDir, const sf::Time& elapsedTime);

    /**
     * A voir si c'est necessaire le pure virtual
     */
    virtual void takeDamage() = 0;
};



#endif //COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
