//
// Created by Antonin Fruchet on 19/06/2026.
//

#include "DangerZone.h"

#include "scripts/GameManager.h"
#include "scripts/entities/PlayerController.h"

DangerZone::DangerZone(const std::string& flag, const std::vector<std::string>& lines, const sf::Vector2f& respawnPoint)
    : flag(flag), lines(lines), respawnPoint(respawnPoint)
{
}

void DangerZone::Start()
{
    Component::Start();
    gameObject->getComponent<Collider>()->setTriggerCallback(
        [this](const std::vector<Collider*>& hits, Collider* self)
            {
               for (const auto& hit : hits)
               {
                   if (auto player = hit->gameObject->getComponent<PlayerController>(); player && !GameManager::checkFlag(flag))
                   {
                       auto tb = GameManager::getTB();
                       tb->setBuffer(lines);
                       tb->open();
                       player->gameObject->transform.move(respawnPoint);
                   }
               }
            }
    );
}
void DangerZone::Update(const sf::Time& elapsedTime)
{
    Component::Update(elapsedTime);
}


