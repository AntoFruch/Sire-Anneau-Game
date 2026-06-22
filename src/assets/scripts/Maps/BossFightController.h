//
// Created by Antonin Fruchet on 21/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_BOSSFIGHTCONTROLLER_H
#define COMPONENT_BASED_ARCH_BOSSFIGHTCONTROLLER_H

#include "Engine.h"
#include "Managers/Scene/ComponentFactory.h"
#include <string>

#include "scripts/entities/BossController.h"
#include "scripts/entities/EnemyController.h"
#include "scripts/entities/EnemySpawner.h"

/** @brief Composant qui sert à gèrer un combat de boss
 *
 */
class BossFightController : public Component
{
    enum class State
    {
        Inactive,
        Waves,      // ennemis seuls
        Boss,       // ennemis + boss
        Completed   // une fois les ennemis vaincu
    };

    static BossFightController* activeFight;    // singleton simple

    std::string completionFlag;     // le flag a set si victoire
    std::string bossPrefab;         // le chemin du prefab du boss
    sf::Vector2f bossSpawnPosition; // position de spawn du boss

    int totalEnemiesToSpawn;    // nombre d'ennemis à tuer en tout
    int killsBeforeBoss;        // nombre d'ennemis à tuer avant que boss ne spawn
    int maxAliveEnemies;        // nombre d'ennemis vivants en même temps
    float spawnInterval;        // intervalle de temps entre deux spawn d'ennemis sur un même spawner

    State state{State::Inactive};                   // Etat du fight
    std::vector<EnemySpawner*> spawners;            // liste des spawner pour ce fight
    std::vector<EnemyController*> aliveEnemies;     // liste des ennemis en vie
    BossController* boss{nullptr};                  // boss

    int spawnedEnemies{0};      // compteur d'ennemis apparus
    int killedEnemies{0};       // compteur d'ennemis tués
    bool bossDead{false};       // boss mort ?

    std::vector<std::string> textOnComplete;   // texte à afficher dans la boite de dialogue une fois le combat gagné

public:
    BossFightController(
        std::string_view completionFlag,
        const std::vector<std::string>& textOnComplete,
        std::string_view bossPrefab,
        float bossX,
        float bossY,
        int totalEnemiesToSpawn,
        int killsBeforeBoss,
        int maxAliveEnemies,
        float spawnInterval);

    ~BossFightController() override;

    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

    /**
     * Donne un pointeur veers le combat actif
     * @return le combat actif
     */
    static BossFightController* getActiveFight();
    /**
     * @brief enregistre le spawner dans la liste.
     * @param spawner
     */
    void registerSpawner(EnemySpawner* spawner);

    int getTotalEnemies() const;
    int getKilledEnemies() const;

    bool isCompleted() const;

private:
    void updateWaves();
    void updateBoss();
    void trySpawnEnemy();
    void spawnBoss();
    void completeFight();

    static inline bool s_registered = ComponentFactory::Register("BossFightController",
        [](const pugi::xml_node& node) -> std::unique_ptr<Component>
        {
            std::vector<std::string> textOnComplete{};
            for (const auto& line : node.children("Line"))
            {
                textOnComplete.push_back(line.attribute("text").as_string());
            }
            return std::make_unique<BossFightController>(
                node.attribute("completionFlag").as_string(),
                textOnComplete,
                node.attribute("bossPrefab").as_string(),
                node.attribute("bossX").as_float(),
                node.attribute("bossY").as_float(),
                node.attribute("totalEnemiesToSpawn").as_int(),
                node.attribute("killsBeforeBoss").as_int(),
                node.attribute("maxAliveEnemies").as_int(),
                node.attribute("spawnInterval").as_float()
            );
        });
};

#endif //COMPONENT_BASED_ARCH_BOSSFIGHTCONTROLLER_H
