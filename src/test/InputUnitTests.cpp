#include <filesystem>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "Managers/Input/InputAction.h"
#include "Managers/Input/InputManager.h"
#include "exceptions/IllegalOperationException.h"

namespace {

std::filesystem::path testRuntimeRoot()
{
    return std::filesystem::path{TEST_RESOURCES_DIR}.parent_path();
}

sf::Event keyPressedEvent(sf::Keyboard::Key key)
{
    return sf::Event{sf::Event::KeyPressed{key}};
}

class TemporaryInputConfigReplacement {
    std::filesystem::path configPath;
    std::filesystem::path backupPath;

public:
    explicit TemporaryInputConfigReplacement(const std::filesystem::path& replacementPath)
        : configPath(testRuntimeRoot() / "resources/config/input-config.xml"),
          backupPath(testRuntimeRoot() / "resources/config/input-config.xml.bak")
    {
        std::filesystem::rename(configPath, backupPath);
        std::filesystem::copy_file(replacementPath, configPath);
    }

    ~TemporaryInputConfigReplacement()
    {
        std::filesystem::remove(configPath);
        std::filesystem::rename(backupPath, configPath);
    }
};

} // namespace

TEST(InputManagerParsing, ValidKeyboardConfigCreatesExpectedActions)
{
    std::filesystem::current_path(testRuntimeRoot());
    InputManager::init();

    EXPECT_NE(InputManager::findAction("Move"), nullptr);
    EXPECT_NE(InputManager::findAction("Attack"), nullptr);
    EXPECT_NE(InputManager::findAction("Pause"), nullptr);
}

TEST(InputManagerParsing, UnknownActionThrowsControlledException)
{
    std::filesystem::current_path(testRuntimeRoot());
    InputManager::init();

    EXPECT_THROW(static_cast<void>(InputManager::findAction("DoesNotExist")), IllegalOperationException);
}

TEST(InputManagerParsing, InvalidConfigFileThrows)
{
    std::filesystem::current_path(testRuntimeRoot());
    const TemporaryInputConfigReplacement replacement{
        testRuntimeRoot() / "resources/config/malformed-input-config.xml"
    };

    EXPECT_THROW(InputManager::init(), std::exception);
}

TEST(InputManagerParsing, UnsupportedInputTypeThrowsClearException)
{
    std::filesystem::current_path(testRuntimeRoot());
    const TemporaryInputConfigReplacement replacement{
        testRuntimeRoot() / "resources/config/unsupported-input-type-config.xml"
    };

    try
    {
        InputManager::init();
        FAIL() << "Expected IllegalOperationException for unsupported input type";
    }
    catch (const IllegalOperationException& e)
    {
        EXPECT_STREQ(e.what(), "Other input types than Vector2D or Button are not supported");
    }
}

TEST(InputActionKeyboard, ButtonActionUsesConfiguredKeyboardKey)
{
    InputAction action("Attack", std::vector<ButtonBinding>{{sf::Keyboard::Key::P}});

    action.processEvent(keyPressedEvent(sf::Keyboard::Key::P), {sf::Keyboard::Key::P});

    EXPECT_TRUE(action.ReadValue<bool>());
}

TEST(InputActionKeyboard, ButtonActionIgnoresOtherKeyboardKeys)
{
    InputAction action("Attack", std::vector<ButtonBinding>{{sf::Keyboard::Key::P}});

    action.processEvent(keyPressedEvent(sf::Keyboard::Key::A), {sf::Keyboard::Key::A});

    EXPECT_FALSE(action.ReadValue<bool>());
}

TEST(InputActionKeyboard, Vector2DActionReadsConfiguredDirections)
{
    InputAction action(
        "Move",
        std::vector<DirectionalBindings>{{
            sf::Keyboard::Key::Z,
            sf::Keyboard::Key::S,
            sf::Keyboard::Key::Q,
            sf::Keyboard::Key::D
        }});

    action.processEvent(keyPressedEvent(sf::Keyboard::Key::Z), {sf::Keyboard::Key::Z});
    EXPECT_EQ(action.ReadValue<sf::Vector2f>(), sf::Vector2f(0.f, -1.f));

    action.processEvent(keyPressedEvent(sf::Keyboard::Key::S), {sf::Keyboard::Key::S});
    EXPECT_EQ(action.ReadValue<sf::Vector2f>(), sf::Vector2f(0.f, 1.f));

    action.processEvent(keyPressedEvent(sf::Keyboard::Key::Q), {sf::Keyboard::Key::Q});
    EXPECT_EQ(action.ReadValue<sf::Vector2f>(), sf::Vector2f(-1.f, 0.f));

    action.processEvent(keyPressedEvent(sf::Keyboard::Key::D), {sf::Keyboard::Key::D});
    EXPECT_EQ(action.ReadValue<sf::Vector2f>(), sf::Vector2f(1.f, 0.f));
}

TEST(InputActionKeyboard, Vector2DActionClampsOppositeDirections)
{
    InputAction action(
        "Move",
        std::vector<DirectionalBindings>{{
            sf::Keyboard::Key::Z,
            sf::Keyboard::Key::S,
            sf::Keyboard::Key::Q,
            sf::Keyboard::Key::D
        }});

    action.processEvent(
        keyPressedEvent(sf::Keyboard::Key::Z),
        {sf::Keyboard::Key::Z, sf::Keyboard::Key::S, sf::Keyboard::Key::Q, sf::Keyboard::Key::D});

    EXPECT_EQ(action.ReadValue<sf::Vector2f>(), sf::Vector2f(0.f, 0.f));
}

TEST(InputActionKeyboard, WasPerformedThisFrameIsTrueOnlyOnReleasedToPressedTransition)
{
    InputAction action("Attack", std::vector<ButtonBinding>{{sf::Keyboard::Key::P}});

    action.processEvent(keyPressedEvent(sf::Keyboard::Key::P), {sf::Keyboard::Key::P});
    EXPECT_TRUE(action.wasPerformedThisFrame());

    action.resetFrameState();
    action.processEvent(keyPressedEvent(sf::Keyboard::Key::P), {sf::Keyboard::Key::P});
    EXPECT_FALSE(action.wasPerformedThisFrame());
}
