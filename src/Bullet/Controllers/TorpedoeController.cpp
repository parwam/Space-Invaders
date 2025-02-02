#include "../../../include/Bullet/BulletModel.h"
#include "../../../include/Bullet/Controllers/TorpedoController.h"

namespace Bullet
{
    namespace Controller
    {
        TorpedoController::TorpedoController(BulletType bullet_type, Entity::EntityType entity_type) : BulletController(bullet_type, entity_type) { }

        TorpedoController::~TorpedoController() { }

        void TorpedoController::initialize(sf::Vector2f position, MovementDirection direction)
        {
            BulletController::initialize(position, direction);
            bullet_model->setMovementSpeed(torpedo_movement_speed);
        }
    }
}