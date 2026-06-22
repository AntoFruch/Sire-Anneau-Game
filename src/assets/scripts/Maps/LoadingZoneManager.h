//
// Created by Antonin Fruchet on 10/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_LOADINGZONEMANAGER_H
#define COMPONENT_BASED_ARCH_LOADINGZONEMANAGER_H
#include "Engine.h"
#include <string_view>

#include "LoadingZone.h"

/**
 * @brief Manager des LoadingZones
 */
class LoadingZoneManager {

    static std::unordered_map<int, LoadingZone*> loadingZones; // la liste des loadingZones de la scène courante

    static int currentDoorId;  // la porte d'où on vient dans la scene courante

public:
    /**
     * @brief Demande le chargement d'une nouvelle scene
     * @param sceneToLoad chemin de la scene à charger
     * @param targetDoorId id de la porte cible devant laquelle faire apparaitre le joueur
     */
    void static requestLoading(std::string_view sceneToLoad, unsigned int targetDoorId);
    /**
     * @brief donne la position où mettre le joueur en fonction de currentDooId
     * @return la position où mettre le joueur
     */
    static const sf::Vector2f& getSpawnPointFromCurrentDoorId();
    /**
     * @brief Enregistre une loadingZone dans loadingZones
     * @param lz
     */
    static void registerLZ(LoadingZone* lz);
    /**
     * @brief Supprime une loadingZone dans loadingZones
     * @param doorId l'id de la loadingZone à supprimer
     */
    static void unregisterLZ(int doorId);

    /**
     *
     * @return false si le joueur doit etre placé devant une porte, true si il n'y a pas encore eu de porte cible.
     */
    static bool defaultSpawn();

    /**
     * resets the state of this class
     */
    static void reset();
};



#endif //COMPONENT_BASED_ARCH_LOADINGZONEMANAGER_H
