#include "entitymanager.h"
#include "entity.h"
#include "spaceship.h"

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
    for (unsigned int k = 0; k < vEntities.size(); k++) {
        Entity* entity = vEntities[k];
        triggerEvent(EVT_ENTITY_DESTROYED, entity->getId(), 0, 0);
        delete entity;
    }

    vEntities.clear();
}

void EntityManager::addEntity(Entity* entity) {
    vEntities.push_back(entity);
    // TODO: trigger correct event
    // TODO: use factory method, or registration method?
}

void EntityManager::removeEntity(int id) {
    for (unsigned int k = 0; k < vEntities.size(); k++) {
        if (vEntities[k]->getId() == id) {
            Entity* entity = vEntities[k];
            
            vEntities.erase(vEntities.begin() + k);
            triggerEvent(EVT_ENTITY_DESTROYED, entity->getId(), 0, 0);
            delete entity;

            break;
        }
    }
}

Entity* EntityManager::createEntity(EntityType_t entityType) {
    // TODO: create entity factory

    Entity* newEntity = 0;

    switch (entityType) {
        case ENT_ASTEROID:
            //newEntity = new Asteroid();
            break;

        case ENT_BULLET:
            //newEntity = new Bullet();
            break;

        case ENT_SPACESHIP:
            newEntity = new Spaceship();
            break;

        default:
            // TODO: error handling
            break;
    }

    vEntities.push_back(newEntity);
    triggerEvent(EVT_ENTITY_CREATED, newEntity->getId(), 0, 0);    
    return newEntity;
}