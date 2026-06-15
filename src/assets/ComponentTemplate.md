# Creation of a new Component script

## Template

```C++
## Header file (.h)

class NewComponent : public Component // Possible to inherit a class that already inherits Component
{
public:
    NewComponent();
    void Start() override; // Executed once at the beginning when everything's constructed
    void Update(const sf::Time& elapsedTime) override; // Executed every frame

private:
    static inline bool s_registered = ComponentFactory::Register("NewComponent", [](const pugi::xml_node& node) -> std::unique_ptr<Component> {
        return std::make_unique<NewComponent>({extraction of the arguments in the xml node});
    });
};

```
