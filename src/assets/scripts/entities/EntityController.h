//
// Created by Antonin Fruchet on 06/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
#define COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
#include "Engine.h"
#include <functional>

/**
 * @brief Controlleur d'entité, c'est la brique de base pour
 */
class EntityController : public CharacterController {
    float speed;
    int max_hp;
    int strength;


protected:
    int current_hp;
    bool invulnerable = false;
    bool dead{false};
    bool deathHandled{false};

    sf::Vector2f facing{0,1}; // facing bottom by default

    Animator* animator;

    // Callback called when attacking successfully
    std::function<void(const std::vector<Collider*>&, Collider*)> attackCallback;
    EventCallback deathCallback;

    GameObject* attackTriggerGO;

public:
    EntityController(float speed, int max_hp, int strength);
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    /**
     * @brief Handles the movement of the entity with the speed, from a direction only
     * @param rawDir entity will move toward this direction, direction is not needed to be normalized
     * @param elapsedTime time between last frame and this frame
     */
    void moveEntity(const sf::Vector2f& rawDir, const sf::Time& elapsedTime);

    virtual void attack();
    void endAttack();

    /**
     * A voir si c'est necessaire le pure virtual
     */
    virtual void takeDamage(int amount);
    virtual void die();
    void setDeathCallback(EventCallback callback);
    float getHealthRatio() const;
};



#endif //COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
