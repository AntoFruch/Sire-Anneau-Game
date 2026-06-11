//
// Created by Antonin Fruchet on 06/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
#define COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
#include "Engine.h"
#include <functional>


class EntityController : public CharacterController {
    float speed;
    int max_hp;
    int strength;
    int current_hp;

protected:
    sf::Vector2f facing{0,1}; // facing bottom by default

    // Callback called when attacking successfully
    // void(*attackCallback)(const std::vector<Collider*>&, Collider*);
    std::function<void(const std::vector<Collider*>&, Collider*)> attackCallback;

public:
    EntityController(const sf::Vector2f& colliderPos, const sf::Vector2f& colliderSize, float speed, int max_hp, int strength);
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
    virtual void takeDamage(int amount)=0;
    float getHealthRatio() const;
};



#endif //COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
