#include "../../include/Elements/ElementService.h"
#include "../../include/Collision/CollisionService.h"
#include "../../include/Global/ServiceLocator.h"

namespace Element
{
    ElementService::ElementService() { }
    ElementService::~ElementService() { destroy(); }

    void ElementService::initialize() { spawnBunkers(); }

    void ElementService::update()
    {
        for (Bunker::BunkerController* bunker : bunker_list)
        {
            bunker->update();
        }

        destroyFlaggedBunkers();
    }

    void ElementService::render()
    {
        for (Bunker::BunkerController* bunker : bunker_list)
        {
            bunker->render();
        }
    }

    void ElementService::spawnBunkers()
    {
        for (int i = 0; i < bunker_data_list.size(); i++)
        {
            Bunker::BunkerController* bunker_controller = new Bunker::BunkerController();

            bunker_controller->initialize(bunker_data_list[i]);
            bunker_list.push_back(bunker_controller);

            Global::ServiceLocator::getInstance()->getCollisionService()->addCollider(dynamic_cast<Collision::ICollider*>(bunker_controller));
        }
    }

    void ElementService::destroyBunker(Bunker::BunkerController* bunker_controller)
    {
        flagged_bunker_list.push_back(bunker_controller);
        bunker_list.erase(std::remove(bunker_list.begin(), bunker_list.end(), bunker_controller), bunker_list.end());
    }

    void ElementService::destroyFlaggedBunkers()
    {
        for (int i = 0; i < flagged_bunker_list.size(); i++)
        {
            Global::ServiceLocator::getInstance()->getCollisionService()->removeCollider(flagged_bunker_list[i]);
            delete (flagged_bunker_list[i]);
        }
        
        flagged_bunker_list.clear();
    }

    void ElementService::destroy()
    {
        for (int i = 0; i < bunker_list.size(); i++)
        {
            Global::ServiceLocator::getInstance()->getCollisionService()->removeCollider(bunker_list[i]);
            delete (bunker_list[i]);
        }
        
        bunker_list.clear();
    }

    void ElementService::reset()
    {
        destroy();
        spawnBunkers();
    }
}
