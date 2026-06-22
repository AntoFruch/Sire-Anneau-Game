//
// Created by Antonin Fruchet on 19/06/2026.
//

#ifndef COMPONENT_BASED_ARCH_DANGERZONE_H
#define COMPONENT_BASED_ARCH_DANGERZONE_H


#include "Engine.h"

/**
 * Composant qui doit être allié à un composant Collider en mode trigger.
 * Permet de bloquer le passage et d'afficher une boite de dialogue.
 */
class DangerZone : public Component
{
    std::string flag;               // flag qui desactive la zone
    std::vector<std::string> lines; // texte à afficher
    sf::Vector2f respawnPoint;      // point de respawn relatif après avoir touché la boite de collision

public:
    DangerZone(const std::string& flag, const std::vector<std::string>& lines, const sf::Vector2f& respawnPoint);
    void Start() override;
    void Update(const sf::Time& elapsedTime) override;

private:
    static inline bool s_registered = ComponentFactory::Register("DangerZone",
     [](const pugi::xml_node& node) -> std::unique_ptr<Component>
     {
         std::vector<std::string> lines{};
         for (const auto& line : node.children("Line"))
         {
             lines.push_back(line.attribute("text").as_string());
         }

         return std::make_unique<DangerZone>(
                 node.attribute("flag").as_string(),
                 lines,
                 sf::Vector2f{
                 node.attribute("respawnX").as_float(),
                 node.attribute("respawnY").as_float()
                 });
     });
};


#endif //COMPONENT_BASED_ARCH_DANGERZONE_H
