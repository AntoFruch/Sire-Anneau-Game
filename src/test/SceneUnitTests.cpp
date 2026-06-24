#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include "Managers/Scene/ComponentFactory.h"
#include "Managers/Scene/Scene.h"
#include "Components/Component.h"
#include "exceptions/IllegalOperationException.h"

namespace {

constexpr auto kRoot = TEST_RESOURCES_DIR "/scene_parser/";
constexpr auto kPrefabRoot = TEST_RESOURCES_DIR "/prefabs/";

class SceneParserProbeComponent : public Component {
    int value;

public:
    explicit SceneParserProbeComponent(int value) : value(value)
    {}

    int getValue() const
    {
        return value;
    }
};

[[maybe_unused]] const bool kProbeRegistered = ComponentFactory::Register(
    "SceneParserProbeComponent",
    [](const pugi::xml_node& node) -> std::unique_ptr<Component>
    {
        return std::make_unique<SceneParserProbeComponent>(node.attribute("value").as_int());
    });

Scene makeScene()
{
    std::filesystem::current_path(std::filesystem::path{TEST_RESOURCES_DIR}.parent_path());
    return Scene();
}

void expectIllegalOperationWithMessage(const auto& operation, const std::string& expectedMessagePart)
{
    try
    {
        operation();
        FAIL() << "Expected IllegalOperationException containing: " << expectedMessagePart;
    }
    catch (const IllegalOperationException& e)
    {
        EXPECT_NE(std::string{e.what()}.find(expectedMessagePart), std::string::npos)
            << "Actual exception message: " << e.what();
    }
}

} // namespace

TEST(SceneParsing, MissingSceneFileThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "missing_scene.xml"); },
        "Could not open scene because");
}

TEST(SceneParsing, MalformedSceneXmlThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "malformed_scene.xml"); },
        "Could not open scene because");
}

TEST(SceneParsing, WrongRootThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "wrong_root_scene.xml"); },
        "Root node of scene must be named \"Scene\"");
}

TEST(SceneParsing, EmptySceneLoads)
{
    auto scene = makeScene();

    EXPECT_NO_THROW(scene.load(std::string{kRoot} + "empty_scene.xml"));
    EXPECT_EQ(scene.dump(), "Scene :\n");
}

TEST(SceneParsing, SingleGameObjectLoads)
{
    auto scene = makeScene();

    ASSERT_NO_THROW(scene.load(std::string{kRoot} + "single_gameobject_scene.xml"));
    EXPECT_NE(scene.dump().find("- Player"), std::string::npos);
}

TEST(SceneParsing, NestedGameObjectsLoad)
{
    auto scene = makeScene();

    ASSERT_NO_THROW(scene.load(std::string{kRoot} + "nested_gameobjects_scene.xml"));
    const std::string dump = scene.dump();
    EXPECT_NE(dump.find("- Parent"), std::string::npos);
    EXPECT_NE(dump.find("- Child"), std::string::npos);
}

TEST(SceneParsing, UnknownSceneChildThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "unknown_scene_child.xml"); },
        "Node Scene children must be GameObject, Prefab or UI");
}

TEST(SceneParsing, UnknownGameObjectChildThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "unknown_gameobject_child.xml"); },
        "GameObject children must be Components, GameObject or Prefab");
}

TEST(SceneParsing, EmptyComponentsNodeLoads)
{
    auto scene = makeScene();

    EXPECT_NO_THROW(scene.load(std::string{kRoot} + "empty_components_scene.xml"));
}

TEST(SceneParsing, ComponentWithoutNameThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "component_without_name.xml"); },
        "Component node must have a non-empty \"name\" attribute");
}

TEST(SceneParsing, NonComponentChildInsideComponentsThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "non_component_inside_components.xml"); },
        "Components node children must be named \"Component\"");
}

TEST(SceneParsing, UnknownComponentThrowsInsteadOfReturningNull)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "unknown_component_scene.xml"); },
        "Class DoesNotExist does not exist.");
}

TEST(SceneParsing, PrefabLoadsAndLabelCanBeOverridden)
{
    auto scene = makeScene();

    ASSERT_NO_THROW(scene.load(std::string{kRoot} + "prefab_override_scene.xml"));
    const std::string dump = scene.dump();
    EXPECT_NE(dump.find("- OverrideName"), std::string::npos);
    EXPECT_EQ(dump.find("- BasePrefab"), std::string::npos);
}

TEST(SceneParsing, PrefabWithoutSrcThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "prefab_without_src_scene.xml"); },
        "Prefab node must have a non-empty \"src\" attribute");
}

TEST(SceneParsing, MissingPrefabFileThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "missing_prefab_scene.xml"); },
        "Could not open prefab because");
}

TEST(SceneParsing, PrefabWithWrongRootThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.load(std::string{kRoot} + "prefab_wrong_root_scene.xml"); },
        "Prefab files must have a unique root node named \"GameObject\"");
}

TEST(SceneParsing, NestedPrefabLoads)
{
    auto scene = makeScene();

    ASSERT_NO_THROW(scene.load(std::string{kRoot} + "nested_prefab_scene.xml"));
    const std::string dump = scene.dump();
    EXPECT_NE(dump.find("- Spawner"), std::string::npos);
    EXPECT_NE(dump.find("- ChildPrefab"), std::string::npos);
}

TEST(SceneParsing, RequestInstantiateValidPrefabReturnsPointer)
{
    auto scene = makeScene();

    GameObject* instantiated = nullptr;
    ASSERT_NO_THROW(instantiated = scene.requestInstantiate(std::string{kPrefabRoot} + "base_prefab.xml"));
    ASSERT_NE(instantiated, nullptr);
    EXPECT_EQ(instantiated->getLabel(), "BasePrefab");
}

TEST(SceneParsing, RequestInstantiateMissingPrefabThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.requestInstantiate(std::string{kPrefabRoot} + "missing_prefab.xml"); },
        "Could not open prefab because");
}

TEST(SceneParsing, RequestInstantiateEmptyPathThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.requestInstantiate(""); },
        "Prefab path must be non-empty");
}

TEST(SceneParsing, GameObjectTransformXmlAttributesAreApplied)
{
    auto scene = makeScene();

    GameObject* instantiated = nullptr;
    ASSERT_NO_THROW(instantiated = scene.requestInstantiate(std::string{kPrefabRoot} + "transform_prefab.xml"));
    ASSERT_NE(instantiated, nullptr);

    EXPECT_EQ(instantiated->getLabel(), "TransformedPrefab");
    EXPECT_FLOAT_EQ(instantiated->transform.getLocalPosition().x, 12.5f);
    EXPECT_FLOAT_EQ(instantiated->transform.getLocalPosition().y, -3.25f);
    EXPECT_FLOAT_EQ(instantiated->transform.getLocalRotation().asDegrees(), 45.f);
    EXPECT_FLOAT_EQ(instantiated->transform.getLocalScale().x, 2.f);
    EXPECT_FLOAT_EQ(instantiated->transform.getLocalScale().y, 0.5f);
}

TEST(SceneParsing, GameObjectMissingXmlAttributesUseDefaults)
{
    auto scene = makeScene();

    GameObject* instantiated = nullptr;
    ASSERT_NO_THROW(instantiated = scene.requestInstantiate(std::string{kPrefabRoot} + "default_gameobject_prefab.xml"));
    ASSERT_NE(instantiated, nullptr);

    EXPECT_EQ(instantiated->getLabel(), "DefaultsOnly");
    EXPECT_FLOAT_EQ(instantiated->transform.getLocalPosition().x, 0.f);
    EXPECT_FLOAT_EQ(instantiated->transform.getLocalPosition().y, 0.f);
    EXPECT_FLOAT_EQ(instantiated->transform.getLocalRotation().asDegrees(), 0.f);
    EXPECT_FLOAT_EQ(instantiated->transform.getLocalScale().x, 1.f);
    EXPECT_FLOAT_EQ(instantiated->transform.getLocalScale().y, 1.f);
}

TEST(SceneParsing, PrefabKeepsItsChildrenAndComponents)
{
    auto scene = makeScene();

    GameObject* instantiated = nullptr;
    ASSERT_NO_THROW(instantiated = scene.requestInstantiate(std::string{kPrefabRoot} + "prefab_with_child_and_component.xml"));
    ASSERT_NE(instantiated, nullptr);

    auto probe = instantiated->getComponent<SceneParserProbeComponent>();
    ASSERT_NE(probe, nullptr);
    EXPECT_EQ(probe->gameObject, instantiated);
    EXPECT_EQ(probe->getValue(), 42);

    GameObject* child = instantiated->getChild("PrefabChild");
    ASSERT_NE(child, nullptr);
    EXPECT_FLOAT_EQ(child->transform.getLocalPosition().x, 4.f);
    EXPECT_FLOAT_EQ(child->transform.getLocalPosition().y, 8.f);
}

TEST(SceneParsing, RequestInstantiateAddsObjectOnlyOnNextUpdate)
{
    auto scene = makeScene();

    ASSERT_EQ(scene.dump(), "Scene :\n");

    GameObject* instantiated = nullptr;
    ASSERT_NO_THROW(instantiated = scene.requestInstantiate(std::string{kPrefabRoot} + "base_prefab.xml"));
    ASSERT_NE(instantiated, nullptr);
    EXPECT_EQ(scene.dump(), "Scene :\n");

    scene.Update(sf::Time::Zero);
    EXPECT_NE(scene.dump().find("- BasePrefab"), std::string::npos);
}

TEST(SceneParsing, UnloadMustBeCalledBeforeLoadingAReplacementScene)
{
    auto scene = makeScene();

    ASSERT_NO_THROW(scene.load(std::string{kRoot} + "single_gameobject_scene.xml"));
    ASSERT_NE(scene.dump().find("- Player"), std::string::npos);

    ASSERT_NO_THROW(scene.load(std::string{kRoot} + "empty_scene.xml"));
    EXPECT_NE(scene.dump().find("- Player"), std::string::npos);

    scene.unload();
    EXPECT_EQ(scene.dump(), "Scene :\n");

    ASSERT_NO_THROW(scene.load(std::string{kRoot} + "empty_scene.xml"));
    EXPECT_EQ(scene.dump(), "Scene :\n");
}
