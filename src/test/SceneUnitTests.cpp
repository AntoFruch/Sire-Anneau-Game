// Généré entièrement par Codex avec les prompts suivants :
//   >> Regarde le parsing de Scene et donne moi une liste de cas à tester pour
//      vérifier qu'il n'y a pas de crash pas voulu, que ça retourne les bonnes exceptions etc.
//
//   >> ok ecris les tests pour ça dans un fichier SceneUnitTests, créé des resources spéciales pour
//      les tests aussi n'hésite pas si tu penses que certains endroits dans le code devrait
//      retourner des exceptions ou des choses comme ça à le mettre dans les tests et expliquer pourquoi.
//
// Le dossier de resources de test scene_parser a aussi entièrement été généré par Codex.

#include <filesystem>
#include <string>

#include <gtest/gtest.h>

#include "Managers/Scene/ComponentFactory.h"
#include "Managers/Scene/Scene.h"
#include "exceptions/IllegalOperationException.h"

namespace {

constexpr auto kRoot = TEST_RESOURCES_DIR "/scene_parser/";

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
    ASSERT_NO_THROW(instantiated = scene.requestInstantiate(std::string{kRoot} + "prefabs/base_prefab.xml"));
    ASSERT_NE(instantiated, nullptr);
    EXPECT_EQ(instantiated->getLabel(), "BasePrefab");
}

TEST(SceneParsing, RequestInstantiateMissingPrefabThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.requestInstantiate(std::string{kRoot} + "prefabs/missing_prefab.xml"); },
        "Could not open prefab because");
}

TEST(SceneParsing, RequestInstantiateEmptyPathThrows)
{
    auto scene = makeScene();

    expectIllegalOperationWithMessage(
        [&] { scene.requestInstantiate(""); },
        "Prefab path must be non-empty");
}
