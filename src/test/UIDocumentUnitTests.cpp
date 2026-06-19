#include <memory>
#include <vector>

#include <gtest/gtest.h>
#include <TGUI/Backend/Font/BackendFontFactory.hpp>
#include <TGUI/Backend/Font/SFML-Graphics/BackendFontSFML.hpp>
#include <TGUI/Backend/Renderer/SFML-Graphics/BackendRendererSFML.hpp>
#include <TGUI/Backend/Window/Backend.hpp>
#include <TGUI/Backend/Window/SFML/BackendSFML.hpp>
#include <TGUI/Widgets/Panel.hpp>

#include "Components/UIDocument.h"
#include "Managers/Scene/SceneManager.h"

namespace {

class TestUIDocument : public UIDocument {
public:
    [[nodiscard]] bool isHidden() const
    {
        return hidden;
    }

    [[nodiscard]] std::size_t elementCount() const
    {
        return elements.size();
    }
};

class UIDocumentBaseBehavior : public testing::Test {
protected:
    static Scene& managedScene()
    {
        static Scene scene;
        SceneManager::init(&scene);
        return scene;
    }

    static void ensureTguiBackend()
    {
        if (tgui::isBackendSet())
        {
            return;
        }

        auto backend = std::make_shared<tgui::BackendSFML>();
        backend->setFontBackend(std::make_shared<tgui::BackendFontFactoryImpl<tgui::BackendFontSFML>>());
        backend->setRenderer(std::make_shared<tgui::BackendRendererSFML>());
        tgui::setBackend(backend);
    }

    static void clearGui()
    {
        managedScene();
        tgui::Gui* gui = SceneManager::getGui();
        const std::vector<tgui::Widget::Ptr> widgets = gui->getWidgets();
        for (const auto& widget : widgets)
        {
            gui->remove(widget);
        }
    }

    void SetUp() override
    {
        ensureTguiBackend();
        managedScene().unload();
        clearGui();
    }

    void TearDown() override
    {
        clearGui();
    }
};

} // namespace

TEST_F(UIDocumentBaseBehavior, StartUsesCurrentSceneGui)
{
    TestUIDocument document;

    document.Start();
    const auto widget = tgui::Panel::create();
    document.addElement(widget, "HealthLabel");

    EXPECT_EQ(SceneManager::getGui()->get("HealthLabel"), widget);
}

TEST_F(UIDocumentBaseBehavior, AddElementStoresWidgetAndAddsItToGui)
{
    TestUIDocument document;
    document.Start();
    const auto widget = tgui::Panel::create();

    document.addElement(widget, "PauseLabel");

    EXPECT_EQ(document.elementCount(), 1u);
    EXPECT_EQ(SceneManager::getGui()->get("PauseLabel"), widget);
}

TEST_F(UIDocumentBaseBehavior, DestructorRemovesOwnedWidgetsFromGui)
{
    tgui::Widget::Ptr widget;

    {
        TestUIDocument document;
        document.Start();
        widget = tgui::Panel::create();
        document.addElement(widget, "TemporaryLabel");
        ASSERT_EQ(SceneManager::getGui()->get("TemporaryLabel"), widget);
    }

    EXPECT_EQ(SceneManager::getGui()->get("TemporaryLabel"), nullptr);
}

TEST_F(UIDocumentBaseBehavior, HideDisablesAndHidesAllElements)
{
    TestUIDocument document;
    document.Start();
    const auto first = tgui::Panel::create();
    const auto second = tgui::Panel::create();
    document.addElement(first, "FirstLabel");
    document.addElement(second, "SecondLabel");

    document.hide();

    EXPECT_TRUE(document.isHidden());
    EXPECT_FALSE(first->isVisible());
    EXPECT_FALSE(first->isEnabled());
    EXPECT_FALSE(second->isVisible());
    EXPECT_FALSE(second->isEnabled());
}

TEST_F(UIDocumentBaseBehavior, ShowEnablesAndShowsAllElements)
{
    TestUIDocument document;
    document.Start();
    const auto first = tgui::Panel::create();
    const auto second = tgui::Panel::create();
    document.addElement(first, "FirstLabel");
    document.addElement(second, "SecondLabel");
    document.hide();

    document.show();

    EXPECT_FALSE(document.isHidden());
    EXPECT_TRUE(first->isVisible());
    EXPECT_TRUE(first->isEnabled());
    EXPECT_TRUE(second->isVisible());
    EXPECT_TRUE(second->isEnabled());
}
