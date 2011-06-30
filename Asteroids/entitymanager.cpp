#include "entitymanager.h"
#include "entity.h"
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
    purge();
}

Entity* EntityManager::createEntity(EntityType_t entityType) {
    Entity* newEntity = 0;

    switch (entityType) {
        case ENT_ASTEROID:
            newEntity = new Asteroid();
            break;

        case ENT_BULLET:
            newEntity = new Bullet();
            break;

        case ENT_SPACESHIP:
            newEntity = new Spaceship();
            break;

        default:
            return 0;
            break;
    }

    vEntities.push_back(newEntity);
    triggerEvent(EVT_ENTITY_CREATED, newEntity->getId(), static_cast<int>(entityType), static_cast<void*>(newEntity));    
    
    return newEntity;
}

void EntityManager::removeEntity(int id) {
    for (unsigned int k = 0; k < vEntities.size(); k++) {
        if (vEntities[k]->getId() == id) {
            Entity* entity = vEntities[k];
            
            vEntities.erase(vEntities.begin() + k);

            // This will signal the entity representation manager and other listeners
            // that an entity is no longer valid
            triggerEvent(EVT_ENTITY_DESTROYED, entity->getId(), 0, 0);
            delete entity;

            break;
        }
    }
}

void EntityManager::purge() {
    for (unsigned int k = 0; k < vEntities.size(); k++) {
        Entity* entity = vEntities[k];

        // This will signal the entity representation manager and other listeners
        // that an entity is no longer valid
        triggerEvent(EVT_ENTITY_DESTROYED, entity->getId(), 0, 0);
        delete entity;
    }

    vEntities.clear();
}

void EntityManager::updateAll(int dt) {
    for (unsigned int k = 0; k < vEntities.size(); k++) {
        Entity* entity = vEntities[k];
        entity->update(dt);
    }
}