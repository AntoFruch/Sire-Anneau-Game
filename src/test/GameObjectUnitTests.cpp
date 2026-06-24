#include <memory>
#include <stdexcept>
#include <vector>

#include <gtest/gtest.h>

#include "Components/Component.h"
#include "GameObject.h"
#include "Managers/Scene/Scene.h"

namespace {

GameObject makeGameObject(bool active = true)
{
    return GameObject("TestObject", {0.f, 0.f}, sf::degrees(0.f), {1.f, 1.f}, active);
}

class ProbeComponent : public Component {
public:
    int startCount{0};
    int updateCount{0};

    void Start() override
    {
        ++startCount;
    }

    void Update(const sf::Time& elapsedTime) override
    {
        ++updateCount;
    }
};

class DerivedProbeComponent : public ProbeComponent {
};

class OtherComponent : public Component {
};

class AddComponentOnStart : public Component {
public:
    void Start() override
    {
        gameObject->addComponent(std::make_unique<ProbeComponent>());
    }
};

} // namespace

TEST(GameObjectComponents, AddComponentAssignsParentGameObject)
{
    auto gameObject = makeGameObject();
    auto component = std::make_unique<ProbeComponent>();
    ProbeComponent* rawComponent = component.get();

    gameObject.addComponent(std::move(component));

    EXPECT_EQ(rawComponent->gameObject, &gameObject);
}

TEST(GameObjectComponents, GetComponentReturnsExistingComponent)
{
    auto gameObject = makeGameObject();
    auto component = std::make_unique<ProbeComponent>();
    ProbeComponent* rawComponent = component.get();
    gameObject.addComponent(std::move(component));

    EXPECT_EQ(gameObject.getComponent<ProbeComponent>(), rawComponent);
}

TEST(GameObjectComponents, GetComponentReturnsNullptrWhenComponentIsMissing)
{
    auto gameObject = makeGameObject();

    EXPECT_EQ(gameObject.getComponent<ProbeComponent>(), nullptr);
}

TEST(GameObjectComponents, GetComponentReturnsFirstCompatibleComponent)
{
    auto gameObject = makeGameObject();
    auto first = std::make_unique<ProbeComponent>();
    auto second = std::make_unique<DerivedProbeComponent>();
    ProbeComponent* firstRaw = first.get();

    gameObject.addComponent(std::move(first));
    gameObject.addComponent(std::move(second));

    EXPECT_EQ(gameObject.getComponent<ProbeComponent>(), firstRaw);
}

TEST(GameObjectComponents, GetComponentsReturnsAllCompatibleComponents)
{
    auto gameObject = makeGameObject();
    auto first = std::make_unique<ProbeComponent>();
    auto second = std::make_unique<DerivedProbeComponent>();
    auto ignored = std::make_unique<OtherComponent>();
    ProbeComponent* firstRaw = first.get();
    DerivedProbeComponent* secondRaw = second.get();

    gameObject.addComponent(std::move(first));
    gameObject.addComponent(std::move(ignored));
    gameObject.addComponent(std::move(second));

    const std::vector<ProbeComponent*> components = gameObject.getComponents<ProbeComponent>();
    ASSERT_EQ(components.size(), 2);
    EXPECT_EQ(components[0], firstRaw);
    EXPECT_EQ(components[1], secondRaw);
}

TEST(GameObjectComponents, GetComponentsReturnsEmptyListWhenComponentIsMissing)
{
    auto gameObject = makeGameObject();
    gameObject.addComponent(std::make_unique<OtherComponent>());

    EXPECT_TRUE(gameObject.getComponents<ProbeComponent>().empty());
}

TEST(GameObjectLifecycle, StartIsCalledOncePerComponentForEachStartCall)
{
    auto gameObject = makeGameObject();
    auto first = std::make_unique<ProbeComponent>();
    auto second = std::make_unique<ProbeComponent>();
    ProbeComponent* firstRaw = first.get();
    ProbeComponent* secondRaw = second.get();

    gameObject.addComponent(std::move(first));
    gameObject.addComponent(std::move(second));

    gameObject.start();

    EXPECT_EQ(firstRaw->startCount, 1);
    EXPECT_EQ(secondRaw->startCount, 1);
}

TEST(GameObjectLifecycle, UpdateIsNotCalledOnInactiveGameObject)
{
    auto gameObject = makeGameObject(false);
    auto component = std::make_unique<ProbeComponent>();
    ProbeComponent* rawComponent = component.get();
    gameObject.addComponent(std::move(component));

    gameObject.update(sf::seconds(1.f));

    EXPECT_EQ(rawComponent->updateCount, 0);
}

TEST(GameObjectLifecycle, InactiveChildDoesNotUpdateItsComponents)
{
    auto parent = makeGameObject();
    auto child = std::make_unique<GameObject>("InactiveChild", sf::Vector2f{0.f, 0.f}, sf::degrees(0.f), sf::Vector2f{1.f, 1.f}, false);
    auto component = std::make_unique<ProbeComponent>();
    ProbeComponent* rawComponent = component.get();

    child->addComponent(std::move(component));
    parent.addChild(std::move(child));

    parent.update(sf::seconds(1.f));

    EXPECT_EQ(rawComponent->updateCount, 0);
}

TEST(GameObjectLifecycle, ChildIsInactiveWhenParentIsInactive)
{
    auto parent = makeGameObject(false);
    auto child = std::make_unique<GameObject>("ActiveChild", sf::Vector2f{0.f, 0.f}, sf::degrees(0.f), sf::Vector2f{1.f, 1.f}, true);
    GameObject* rawChild = child.get();

    parent.addChild(std::move(child));

    EXPECT_FALSE(rawChild->isActive());
}

TEST(GameObjectLifecycle, DestroySelfMarksObjectForDestruction)
{
    auto gameObject = makeGameObject();

    EXPECT_FALSE(gameObject.isWaitingDestruction());

    gameObject.destroySelf();

    EXPECT_TRUE(gameObject.isWaitingDestruction());
}

TEST(GameObjectLifecycle, SceneRemovesDestroyedObjectsOnUpdate)
{
    Scene scene;
    GameObject* gameObject = scene.requestInstantiate(TEST_RESOURCES_DIR "/prefabs/base_prefab.xml");
    ASSERT_NE(gameObject, nullptr);

    scene.Update(sf::Time::Zero);
    ASSERT_NE(scene.dump().find("- BasePrefab"), std::string::npos);

    gameObject->destroySelf();
    scene.Update(sf::Time::Zero);

    EXPECT_EQ(scene.dump(), "Scene :\n");
}

TEST(GameObjectLifecycle, AddingComponentDuringStartDoesNotBreakComponentIteration)
{
    auto gameObject = makeGameObject();
    auto component = std::make_unique<AddComponentOnStart>();
    AddComponentOnStart* rawComponent = component.get();

    gameObject.addComponent(std::move(component));

    ASSERT_NO_FATAL_FAILURE(gameObject.start());
    EXPECT_EQ(rawComponent->gameObject, &gameObject);
    EXPECT_NE(gameObject.getComponent<ProbeComponent>(), nullptr);
}
