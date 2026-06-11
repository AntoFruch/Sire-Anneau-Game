//
// Created by hugo on 11/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_HUDMANAGER_H
#define COMPONENT_BASED_ARCH_HUDMANAGER_H

class PlayerController;

class HUDManager {
    static PlayerController* activePlayer;

public:
    static void registerPlayer(PlayerController* player);
    static PlayerController* getPlayer();
};

#endif //COMPONENT_BASED_ARCH_HUDMANAGER_H
