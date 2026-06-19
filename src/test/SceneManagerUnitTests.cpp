#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "Components/Component.h"
#include "Managers/Scene/ComponentFactory.h"
#include "Managers/Scene/SceneManager.h"

namespace {

constexpr auto kRoot = TEST_RESOURCES_DIR "/scene_manager/";
constexpr auto kPrefabRoot = TEST_RESOURCES_DIR "/prefabs/";

class SceneManagerUpdateProbe : public Component {
public:
    static inline int updateCount = 0;

    void Update(const sf::Time& elapsedTime) override
    {
        ++updateCount;
    }
};

[[maybe_unused]] const bool kUpdateProbeRegistered = ComponentFactory::Register(
    "SceneManagerUpdateProbe",
    [](const pugi::xml_node& node) -> std::unique_ptr<Component>
    {
        return std::make_unique<SceneManagerUpdateProbe>();
    });

class SceneManagerNavigation : public testing::Test {
protected:
    static Scene& managedScene()
    {
        static Scene scene;
        SceneManager::init(&scene);
        return scene;
    }

    void SetUp() override
    {
        managedScene();
        SceneManager::unfreeze();
        managedScene().unload();
        SceneManagerUpdateProbe::updateCount = 0;
    }
};

bool dumpContains(const std::string& dump, std::string_view text)
{
    return dump.find(text) != std::string::npos;
}

} // namespace

TEST_F(SceneManagerNavigation, RequestLoadingStoresOnePendingSceneLoad)
{
    SceneManager::requestLoading(std::string{kRoot} + "first_scene.xml");

    EXPECT_EQ(managedScene().dump(), "Scene :\n");

    SceneManager::Update(sf::Time::Zero);

    const std::string dump = managedScene().dump();
    EXPECT_TRUE(dumpContains(dump, "- FirstSceneObject"));
}

TEST_F(SceneManagerNavigation, SecondLoadingRequestIsIgnoredWhileOneIsPending)
{
    SceneManager::requestLoading(std::string{kRoot} + "first_scene.xml");
    SceneManager::requestLoading(std::string{kRoot} + "second_scene.xml");

    SceneManager::Update(sf::Time::Zero);

    const std::string dump = managedScene().dump();
    EXPECT_TRUE(dumpContains(dump, "- FirstSceneObject"));
    EXPECT_FALSE(dumpContains(dump, "- SecondSceneObject"));
}

TEST_F(SceneManagerNavigation, ApplyRequestUnloadsCurrentSceneBeforeLoadingNextOne)
{
    managedScene().load(std::string{kRoot} + "first_scene.xml");
    ASSERT_TRUE(dumpContains(managedScene().dump(), "- FirstSceneObject"));

    SceneManager::requestLoading(std::string{kRoot} + "second_scene.xml");
    SceneManager::Update(sf::Time::Zero);

    const std::string dump = managedScene().dump();
    EXPECT_FALSE(dumpContains(dump, "- FirstSceneObject"));
    EXPECT_TRUE(dumpContains(dump, "- SecondSceneObject"));
}

TEST_F(SceneManagerNavigation, FreezeBlocksGameplayUpdates)
{
    SceneManager::requestLoading(std::string{kRoot} + "update_probe_scene.xml");
    SceneManager::Update(sf::Time::Zero);

    ASSERT_EQ(SceneManagerUpdateProbe::updateCount, 0);

    SceneManager::freeze();
    SceneManager::Update(sf::seconds(1.f));

    EXPECT_EQ(SceneManagerUpdateProbe::updateCount, 0);
}

TEST_F(SceneManagerNavigation, UnfreezeResumesGameplayUpdates)
{
    SceneManager::requestLoading(std::string{kRoot} + "update_probe_scene.xml");
    SceneManager::Update(sf::Time::Zero);

    SceneManager::freeze();
    SceneManager::Update(sf::seconds(1.f));
    ASSERT_EQ(SceneManagerUpdateProbe::updateCount, 0);

    SceneManager::unfreeze();
    SceneManager::Update(sf::seconds(1.f));

    EXPECT_EQ(SceneManagerUpdateProbe::updateCount, 1);
}

TEST_F(SceneManagerNavigation, InstantiateDelegatesToCurrentScene)
{
    GameObject* instantiated = nullptr;

    ASSERT_NO_THROW(instantiated = SceneManager::instantiate(std::string{kPrefabRoot} + "base_prefab.xml"));
    ASSERT_NE(instantiated, nullptr);
    EXPECT_EQ(managedScene().dump(), "Scene :\n");

    SceneManager::Update(sf::Time::Zero);

    EXPECT_TRUE(dumpContains(managedScene().dump(), "- BasePrefab"));
}

TEST_F(SceneManagerNavigation, GetGuiReturnsCurrentSceneGui)
{
    EXPECT_EQ(SceneManager::getGui(), managedScene().getGui());
}
