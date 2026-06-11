//
// Created by hugo on 11/06/2026.
//

#include "HUDManager.h"

// Initialisation de la variable statique
PlayerController* HUDManager::activePlayer = nullptr;

void HUDManager::registerPlayer(PlayerController* player) {
    activePlayer = player;
}

PlayerController* HUDManager::getPlayer() {
    return activePlayer;
}
