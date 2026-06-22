//
// Created by Antonin Fruchet on 11/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_GAMEMANAGER_H
#define COMPONENT_BASED_ARCH_GAMEMANAGER_H
#include "entities/PlayerController.h"
#include "UI/HUD/TextBox.h"

/**
 * @brief Manager de Jeu global
 */
class GameManager {
    static PlayerController* player; // reference vers le joueur

    static TextBox* textBox;    // reference vers la textBox

    static std::unordered_map<std::string, bool> flags;     // flags du jeu (nom, valeur)

public:
    static void registerPlayer(PlayerController*);
    static void unregisterPlayer(PlayerController*);
    static PlayerController* getPlayer();

    static void registerTB(TextBox*);
    static void unregisterTB(TextBox*);
    static TextBox* getTB();

    static void setFlag(const std::string& flagName);
    static bool checkFlag(const std::string& flagName);
};



#endif //COMPONENT_BASED_ARCH_GAMEMANAGER_H
