#include <gtest/gtest.h>

#include <algorithm>

#include "Transform.h"

namespace {

void expectVectorNear(const sf::Vector2f& actual, const sf::Vector2f& expected)
{
    EXPECT_FLOAT_EQ(actual.x, expected.x);
    EXPECT_FLOAT_EQ(actual.y, expected.y);
}

} // namespace

TEST(TransformBasics, DefaultLocalPositionIsZero)
{
    const Transform transform;

    expectVectorNear(transform.getLocalPosition(), {0.f, 0.f});
}

TEST(TransformBasics, LocalMutatorsUpdateLocalValues)
{
    Transform transform({1.f, 2.f}, sf::degrees(10.f), {2.f, 3.f}, nullptr);

    transform.setLocalPosition({10.f, 20.f});
    expectVectorNear(transform.getLocalPosition(), {10.f, 20.f});

    transform.move({5.f, -3.f});
    expectVectorNear(transform.getLocalPosition(), {15.f, 17.f});

    transform.setLocalRotation(sf::degrees(30.f));
    transform.rotate(sf::degrees(15.f));
    EXPECT_FLOAT_EQ(transform.getLocalRotation().asDegrees(), 45.f);

    transform.setLocalScale({2.f, 4.f});
    transform.rescale({3.f, 0.5f});
    expectVectorNear(transform.getLocalScale(), {6.f, 2.f});
}

TEST(TransformHierarchy, WorldPositionIncludesParentPositionAndScale)
{
    Transform parent({10.f, 20.f}, sf::degrees(0.f), {2.f, 3.f}, nullptr);
    Transform child({4.f, 5.f}, sf::degrees(0.f), {1.f, 1.f}, nullptr);

    parent.addChild(&child);

    expectVectorNear(child.getWorldPosition(), {18.f, 35.f});
}

TEST(TransformHierarchy, WorldPositionRotatesAroundParent)
{
    Transform parent({10.f, 20.f}, sf::degrees(90.f), {1.f, 1.f}, nullptr);
    Transform child({0.f, 3.f}, sf::degrees(0.f), {1.f, 1.f}, nullptr);

    parent.addChild(&child);

    expectVectorNear(child.getWorldPosition(), {7.f, 20.f});
}

TEST(TransformHierarchy, WorldRotationAddsParentRotation)
{
    Transform parent({0.f, 0.f}, sf::degrees(30.f), {1.f, 1.f}, nullptr);
    Transform child({0.f, 0.f}, sf::degrees(15.f), {1.f, 1.f}, nullptr);

    parent.addChild(&child);

    EXPECT_FLOAT_EQ(child.getWorldRotation().asDegrees(), 45.f);
}

TEST(TransformHierarchy, WorldScaleMultipliesParentScale)
{
    Transform parent({0.f, 0.f}, sf::degrees(0.f), {2.f, 3.f}, nullptr);
    Transform child({0.f, 0.f}, sf::degrees(0.f), {4.f, 5.f}, nullptr);

    parent.addChild(&child);

    expectVectorNear(child.getWorldScale(), {8.f, 15.f});
}

TEST(TransformHierarchy, ChildWorldPositionChangesWhenParentMoves)
{
    Transform parent({10.f, 20.f}, sf::degrees(0.f), {1.f, 1.f}, nullptr);
    Transform child({4.f, 5.f}, sf::degrees(0.f), {1.f, 1.f}, nullptr);

    parent.addChild(&child);
    expectVectorNear(child.getWorldPosition(), {14.f, 25.f});

    parent.move({3.f, -2.f});
    expectVectorNear(child.getWorldPosition(), {17.f, 23.f});
}

TEST(TransformHierarchy, ChangingParentUpdatesWorldValuesAndNewParentChildren)
{
    Transform firstParent({10.f, 0.f}, sf::degrees(10.f), {2.f, 2.f}, nullptr);
    Transform secondParent({0.f, 20.f}, sf::degrees(30.f), {3.f, 4.f}, nullptr);
    Transform child({5.f, 6.f}, sf::degrees(5.f), {2.f, 3.f}, nullptr);

    firstParent.addChild(&child);
    expectVectorNear(child.getWorldPosition(), {17.764299f, 13.554174f});
    EXPECT_FLOAT_EQ(child.getWorldRotation().asDegrees(), 15.f);
    expectVectorNear(child.getWorldScale(), {4.f, 6.f});

    secondParent.addChild(&child);
    EXPECT_EQ(std::ranges::find(firstParent.getChildren(), &child), firstParent.getChildren().end());
    EXPECT_EQ(secondParent.getChildren().back(), &child);
    expectVectorNear(child.getWorldPosition(), {0.990381f, 48.284607f});
    EXPECT_FLOAT_EQ(child.getWorldRotation().asDegrees(), 35.f);
    expectVectorNear(child.getWorldScale(), {6.f, 12.f});
}

TEST(TransformHierarchy, EdgeCasesHandleZeroScaleNegativeRotationAndMultipleLevels)
{
    Transform grandParent({10.f, 10.f}, sf::degrees(-90.f), {0.f, 2.f}, nullptr);
    Transform parent({5.f, 5.f}, sf::degrees(-45.f), {3.f, 0.f}, nullptr);
    Transform child({7.f, 8.f}, sf::degrees(15.f), {2.f, 4.f}, nullptr);

    grandParent.addChild(&parent);
    parent.addChild(&child);

    expectVectorNear(parent.getWorldPosition(), {20.f, 10.f});
    expectVectorNear(parent.getWorldScale(), {0.f, 0.f});
    EXPECT_FLOAT_EQ(parent.getWorldRotation().asDegrees(), -135.f);

    expectVectorNear(child.getWorldPosition(), {20.f, 10.f});
    expectVectorNear(child.getWorldScale(), {0.f, 0.f});
    EXPECT_FLOAT_EQ(child.getWorldRotation().asDegrees(), -120.f);
}
