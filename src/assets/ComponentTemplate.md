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
    
};

```

```C++
## Implementation file (.h)

// --- ENREGISTREMENT AUTOMATIQUE ---
// On crée une variable globale/statique anonyme.
// Son seul but est de s'exécuter AVANT le début du jeu pour enregistrer le composant.
namespace {
    const bool registered = []() {
        ComponentFactory::Register("NewComponent", [](const pugi::xml_node& node) {
            return std::make_unique<NewComponent>({extraction of the arguments in the xml node});
        });
        return true;
    }();
}
// --------------------------

```