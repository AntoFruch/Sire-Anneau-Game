//
// Created by Antonin Fruchet on 06/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
#define COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
#include "Engine.h"
#include <functional>

/**
 * @brief Controlleur d'entité, c'est la brique de base pour des entités qui se déplacent, attaquent, prennent de dégats etc.
 */
class EntityController : public CharacterController {
    float speed;    // en px/s
    int max_hp;
    int strength;   // Dégâts infligés


protected:
    int current_hp;

    bool invulnerable = false;
    bool dead{false};
    bool deathHandled{false};   // flag pour savoir si l'action de mort a déjà été effectuée

    sf::Vector2f facing{0,1};   // direction dans laquelle regarde l'entité, vers le bas par default

    Animator* animator;     //pointeur vers le composant Animator, pour gérer le déclenchement d'animations

    TriggerCallback attackCallback; // callback appelé quand l'attaque touche une autre entité
    EventCallback deathCallback;    // callback appelé à la fin de l'animation de mort, settable avec setDeathCallback(), pratique pour les ennemis qui sont géré par un manager de combat qui doit savoir quand ils meurent

    GameObject* attackTriggerGO;    // pointeur vers l'objet qui représente le trigger de l'attaque

public:
    /**
     * @brief Constructeur
     * @param speed vitesse de l'entité
     * @param max_hp vie max de l'entité
     * @param strength dégâts d'attaque de l'entité
     */
    EntityController(float speed, int max_hp, int strength);

    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    /**
     * @brief Gère le mouvement de l'entité avec sa vitesse, uniquement à partir de la direction
     * @param rawDir direction normalisée ou pas dans laquelle l'entité bougera
     * @param elapsedTime temps écoulé depuis la dernière frame
     */
    void moveEntity(const sf::Vector2f& rawDir, const sf::Time& elapsedTime);

    /**
     * @brief déclenche l'attaque en activant le trigger de l'attaque et le déplacant dans la direction ou l'entité regarde
     */
    virtual void attack();
    /**
     * @brief désactive le trigger d'attaque en fin d'attaque
     */
    void endAttack();

    /**
     * @brief inflige amount dégât à l'entité
     * @param amount quantité de dégâts à infliger
     * virtual car possiblement overridable
     */
    virtual void takeDamage(int amount);
    /**
     * @brief déclenche l'animation de mort
     * virtual car possiblement overridable
     */
    virtual void die();
    /**
     * @brief définit le callbcak à la fin de l'animation de mort
     * @param callback
     */
    void setDeathCallback(EventCallback callback);
    /**
     * @brief retourne la proportion de vie restante.
     * @return current_hp / max_hp
     */
    float getHealthRatio() const;
};



#endif //COMPONENT_BASED_ARCH_ENTITYCONTROLLER_H
