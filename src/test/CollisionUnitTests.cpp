#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "Components/CharacterController.h"
#include "Components/Collider.h"
#include "GameObject.h"
#include "Managers/Collisions/CollisionsManager.h"
#include "Managers/Scene/Scene.h"

namespace {

std::unique_ptr<GameObject> makeColliderObject(
    std::string_view label,
    sf::Vector2f position,
    sf::Vector2f size = {10.f, 10.f},
    bool trigger = false,
    bool active = true)
{
    auto gameObject = std::make_unique<GameObject>(
        label,
        position,
        sf::degrees(0.f),
        sf::Vector2f{1.f, 1.f},
        active);

    gameObject->addComponent(std::make_unique<Collider>(
        sf::Vector2f{0.f, 0.f},
        size,
        trigger));

    gameObject->start();
    return gameObject;
}

} // namespace

TEST(CollisionsManagerPhysics, ColliderRegistersOnStartAndUnregistersOnDestruction)
{
    auto trigger = makeColliderObject("Trigger", {0.f, 0.f}, {10.f, 10.f}, true);
    auto solid = makeColliderObject("Solid", {0.f, 0.f});
    Collider* triggerCollider = trigger->getComponent<Collider>();

    ASSERT_EQ(CollisionsManager::checkTrigger(*triggerCollider).size(), 1);

    solid.reset();

    EXPECT_TRUE(CollisionsManager::checkTrigger(*triggerCollider).empty());
}

TEST(CollisionsManagerPhysics, OverlappingRectanglesAreDetectedByTrigger)
{
    auto trigger = makeColliderObject("Trigger", {0.f, 0.f}, {10.f, 10.f}, true);
    auto solid = makeColliderObject("Solid", {4.f, 0.f});

    const std::vector<Collider*> hits = CollisionsManager::checkTrigger(*trigger->getComponent<Collider>());

    ASSERT_EQ(hits.size(), 1);
    EXPECT_EQ(hits[0], solid->getComponent<Collider>());
}

TEST(CollisionsManagerPhysics, SeparatedRectanglesDoNotCollide)
{
    auto trigger = makeColliderObject("Trigger", {0.f, 0.f}, {10.f, 10.f}, true);
    auto solid = makeColliderObject("Solid", {30.f, 0.f});

    EXPECT_TRUE(CollisionsManager::checkTrigger(*trigger->getComponent<Collider>()).empty());
}

TEST(CollisionsManagerPhysics, SolidRectanglesTouchingEdgesDoNotBlockMovementAway)
{
    auto mover = makeColliderObject("Mover", {0.f, 0.f});
    auto obstacle = makeColliderObject("Obstacle", {10.f, 0.f});

    const sf::Vector2f resolved = CollisionsManager::move(*mover->getComponent<Collider>(), {-1.f, 0.f});

    EXPECT_EQ(resolved, sf::Vector2f(-1.f, 0.f));
}

TEST(CollisionsManagerPhysics, TriggerColliderCallsCallbackWithoutBlockingMovement)
{
    auto trigger = makeColliderObject("Trigger", {0.f, 0.f}, {10.f, 10.f}, true);
    auto solid = makeColliderObject("Solid", {0.f, 0.f});
    Collider* triggerCollider = trigger->getComponent<Collider>();

    bool callbackCalled = false;
    std::vector<Collider*> callbackHits;
    triggerCollider->setTriggerCallback(
        [&callbackCalled, &callbackHits](const std::vector<Collider*>& hits, Collider* self)
        {
            callbackCalled = true;
            callbackHits = hits;
        });

    trigger->update(sf::Time::Zero);
    const sf::Vector2f resolved = CollisionsManager::move(*triggerCollider, {5.f, 0.f});

    EXPECT_TRUE(callbackCalled);
    ASSERT_EQ(callbackHits.size(), 1);
    EXPECT_EQ(callbackHits[0], solid->getComponent<Collider>());
    EXPECT_EQ(resolved, sf::Vector2f(5.f, 0.f));
}

TEST(CollisionsManagerPhysics, MoveReturnsZeroOnAxisBlockedBySolidCollider)
{
    auto mover = makeColliderObject("Mover", {0.f, 0.f});
    auto obstacle = makeColliderObject("Obstacle", {10.f, 0.f});

    const sf::Vector2f resolved = CollisionsManager::move(*mover->getComponent<Collider>(), {1.f, 0.f});

    EXPECT_EQ(resolved, sf::Vector2f(0.f, 0.f));
}

TEST(CollisionsManagerPhysics, MoveKeepsUnblockedAxisWhenOtherAxisIsBlocked)
{
    auto mover = makeColliderObject("Mover", {0.f, 0.f});
    auto obstacle = makeColliderObject("Obstacle", {10.f, 0.f});

    const sf::Vector2f resolved = CollisionsManager::move(*mover->getComponent<Collider>(), {1.f, 3.f});

    EXPECT_EQ(resolved, sf::Vector2f(0.f, 3.f));
}

TEST(CollisionsManagerPhysics, InactiveColliderIsNotTakenIntoAccount)
{
    auto trigger = makeColliderObject("Trigger", {0.f, 0.f}, {10.f, 10.f}, true);
    auto inactiveSolid = makeColliderObject("InactiveSolid", {0.f, 0.f}, {10.f, 10.f}, false, false);

    EXPECT_TRUE(CollisionsManager::checkTrigger(*trigger->getComponent<Collider>()).empty());
}

TEST(CollisionsManagerPhysics, DestroyedColliderIsNotTakenIntoAccount)
{
    auto trigger = makeColliderObject("Trigger", {0.f, 0.f}, {10.f, 10.f}, true);
    auto solid = makeColliderObject("Solid", {0.f, 0.f});

    ASSERT_FALSE(CollisionsManager::checkTrigger(*trigger->getComponent<Collider>()).empty());

    solid.reset();

    EXPECT_TRUE(CollisionsManager::checkTrigger(*trigger->getComponent<Collider>()).empty());
}

TEST(CollisionsManagerPhysics, TriggerReportsMultipleHitColliders)
{
    auto trigger = makeColliderObject("Trigger", {0.f, 0.f}, {10.f, 10.f}, true);
    auto firstSolid = makeColliderObject("FirstSolid", {-2.f, 0.f});
    auto secondSolid = makeColliderObject("SecondSolid", {2.f, 0.f});

    const std::vector<Collider*> hits = CollisionsManager::checkTrigger(*trigger->getComponent<Collider>());

    EXPECT_EQ(hits.size(), 2);
    EXPECT_NE(std::ranges::find(hits, firstSolid->getComponent<Collider>()), hits.end());
    EXPECT_NE(std::ranges::find(hits, secondSolid->getComponent<Collider>()), hits.end());
}

TEST(CollisionsManagerPhysics, CharacterControllerMoveUsesCollisionsManagerResolution)
{
    auto character = std::make_unique<GameObject>(
        "Character",
        sf::Vector2f{0.f, 0.f},
        sf::degrees(0.f),
        sf::Vector2f{1.f, 1.f},
        true);
    character->addComponent(std::make_unique<Collider>(sf::Vector2f{0.f, 0.f}, sf::Vector2f{10.f, 10.f}, false));
    character->addComponent(std::make_unique<CharacterController>());
    character->start();
    auto obstacle = makeColliderObject("Obstacle", {10.f, 0.f});

    character->getComponent<CharacterController>()->move({1.f, 3.f});

    EXPECT_EQ(character->transform.getLocalPosition(), sf::Vector2f(0.f, 3.f));
}

TEST(CollisionsManagerPhysics, ColliderSizeIsReadFromXml)
{
    Scene scene;
    GameObject* sizedColliderObject = scene.requestInstantiate(TEST_RESOURCES_DIR "/collisions/collider_size_scene.xml");

    ASSERT_NE(sizedColliderObject, nullptr);
    ASSERT_NE(sizedColliderObject->getComponent<Collider>(), nullptr);
    EXPECT_EQ(sizedColliderObject->getComponent<Collider>()->getSize(), sf::Vector2f(12.f, 34.f));
}
