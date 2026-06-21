//
// Created by Antonin Fruchet on 21/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_BOSSFIGHTCONTROLLER_H
#define COMPONENT_BASED_ARCH_BOSSFIGHTCONTROLLER_H

#include "Engine.h"
#include "Managers/Scene/ComponentFactory.h"
#include <string>

class BossController;
class EnemyController;
class EnemySpawner;
class EntityController;

class BossFightController : public Component
{
    std::vector<std::string> textOnComplete;
    enum class State
    {
        Inactive,
        Waves,
        Boss,
        Completed
    };

    static BossFightController* activeFight;

    std::string completionFlag;
    std::string bossPrefab;
    sf::Vector2f bossSpawnPosition;

    int totalEnemiesToSpawn;
    int killsBeforeBoss;
    int maxAliveEnemies;
    float spawnInterval;

    State state{State::Inactive};
    std::vector<EnemySpawner*> spawners;
    std::vector<EnemyController*> aliveEnemies;
    BossController* boss{nullptr};

    int spawnedEnemies{0};
    int killedEnemiesBeforeBoss{0};
    int killedEnemiesAfterBoss{0};
    bool bossDead{false};

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

    static BossFightController* getActiveFight();
    void registerSpawner(EnemySpawner* spawner);

private:
    void updateWaves();
    void updateBoss();
    void trySpawnEnemy();
    void spawnBoss();
    void completeFight();
    void onEnemyDeath(EnemyController* enemy);
    void onBossDeath();

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
