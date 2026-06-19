#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "Components/Component.h"
#include "Managers/Scene/ComponentFactory.h"
#include "exceptions/IllegalOperationException.h"

namespace {

constexpr auto kRoot = TEST_RESOURCES_DIR "/component_factory/";

class FactoryProbeComponent : public Component {
public:
    int intValue;
    float floatValue;
    std::string stringValue;

    FactoryProbeComponent(int intValue, float floatValue, std::string stringValue)
        : intValue(intValue), floatValue(floatValue), stringValue(std::move(stringValue))
    {}
};

class DuplicateProbeComponent : public Component {
};

pugi::xml_node loadComponentNode(pugi::xml_document& doc, std::string_view path)
{
    const pugi::xml_parse_result result = doc.load_file(path.data());
    EXPECT_TRUE(result) << result.description();
    return doc.child("Component");
}

} // namespace

TEST(ComponentFactoryRegistration, RegisteredComponentCanBeCreatedByName)
{
    constexpr auto componentName = "FactoryProbeCreatable";
    ASSERT_TRUE(ComponentFactory::Register(
        componentName,
        [](const pugi::xml_node& node) -> std::unique_ptr<Component>
        {
            return std::make_unique<FactoryProbeComponent>(0, 0.f, "");
        }));

    pugi::xml_document doc;
    const pugi::xml_node node = loadComponentNode(doc, std::string{kRoot} + "empty_component.xml");

    std::unique_ptr<Component> component;
    ASSERT_NO_THROW(component = ComponentFactory::Create(componentName, node));
    EXPECT_NE(dynamic_cast<FactoryProbeComponent*>(component.get()), nullptr);
}

TEST(ComponentFactoryRegistration, UnknownComponentNameThrowsClearException)
{
    pugi::xml_document doc;
    const pugi::xml_node node = loadComponentNode(doc, std::string{kRoot} + "empty_component.xml");

    try
    {
        static_cast<void>(ComponentFactory::Create("FactoryProbeMissing", node));
        FAIL() << "Expected IllegalOperationException for unknown component name";
    }
    catch (const IllegalOperationException& e)
    {
        EXPECT_NE(std::string{e.what()}.find("Class FactoryProbeMissing does not exist."), std::string::npos)
            << "Actual exception message: " << e.what();
    }
}

TEST(ComponentFactoryRegistration, DuplicateRegistrationThrows)
{
    constexpr auto componentName = "FactoryProbeDuplicate";
    ASSERT_TRUE(ComponentFactory::Register(
        componentName,
        [](const pugi::xml_node& node) -> std::unique_ptr<Component>
        {
            return std::make_unique<FactoryProbeComponent>(1, 0.f, "first");
        }));

    EXPECT_THROW(
        ComponentFactory::Register(
            componentName,
            [](const pugi::xml_node& node) -> std::unique_ptr<Component>
            {
                return std::make_unique<DuplicateProbeComponent>();
            }),
        IllegalOperationException);
}

TEST(ComponentFactoryRegistration, XmlAttributesArePassedToComponentCreator)
{
    constexpr auto componentName = "FactoryProbeWithAttributes";
    ASSERT_TRUE(ComponentFactory::Register(
        componentName,
        [](const pugi::xml_node& node) -> std::unique_ptr<Component>
        {
            return std::make_unique<FactoryProbeComponent>(
                node.attribute("int_value").as_int(),
                node.attribute("float_value").as_float(),
                node.attribute("string_value").as_string());
        }));

    pugi::xml_document doc;
    const pugi::xml_node node = loadComponentNode(doc, std::string{kRoot} + "component_with_attributes.xml");

    std::unique_ptr<Component> component = ComponentFactory::Create(componentName, node);
    auto* probe = dynamic_cast<FactoryProbeComponent*>(component.get());

    ASSERT_NE(probe, nullptr);
    EXPECT_EQ(probe->intValue, 42);
    EXPECT_FLOAT_EQ(probe->floatValue, 3.5f);
    EXPECT_EQ(probe->stringValue, "from_xml");
}
