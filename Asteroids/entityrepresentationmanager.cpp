#include "entityrepresentationmanager.h"
#include "entityrepresentation.h"
#include "spaceshiprepresentation.h"
#include "bulletrepresentation.h"
#include "asteroidrepresentation.h"

EntityRepresentationManager::EntityRepresentationManager() {
}

EntityRepresentationManager::~EntityRepresentationManager() {
    // NOTE: this should not be necessary if all events are handled correctly
    // If there is ever a logger class, this should be logged
    for (unsigned int k = 0; k < mEntityRepresentations.size(); k++) {
        delete mEntityRepresentations[k];
    }
}

void EntityRepresentationManager::onEvent(Event_t eventType, int param1, int param2, void* extra) {
    switch (eventType) {
        case EVT_ENTITY_CREATED:
            mEntityRepresentations[param1] = createRepresentation(static_cast<EntityType_t>(param2));
            mEntityRepresentations[param1]->setEntity(static_cast<Entity*>(extra));
            break;

        case EVT_ENTITY_DESTROYED:
            delete mEntityRepresentations[param1];
            mEntityRepresentations[param1] = 0;
            break;

        default:
            break;
    }
}

EntityRepresentation* EntityRepresentationManager::getRepresentation(int id) {
    return mEntityRepresentations[id];
}

EntityRepresentation* EntityRepresentationManager::createRepresentation(EntityType_t entityType) {
    EntityRepresentation* newRepresentation = 0;

    switch (entityType) {
        case ENT_ASTEROID:
            newRepresentation = new AsteroidRepresentation();
            break;

        case ENT_BULLET:
            newRepresentation = new BulletRepresentation();
            break;

        case ENT_SPACESHIP:
            newRepresentation = new SpaceshipRepresentation();
            break;

        default:
            return 0;
            break;
    }

    return newRepresentation;
}