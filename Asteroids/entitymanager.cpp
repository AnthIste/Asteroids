#include "entitymanager.h"
#include "entity.h"

EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {
    for (unsigned int k = 0; k < vEntities.size(); k++) {
        delete vEntities[k];
    }
}

void EntityManager::addEntity(Entity* entity) {
    vEntities.push_back(entity);
    // TODO: trigger correct event
}

void EntityManager::removeEntity(int id) {
    for (unsigned int k = 0; k < vEntities.size(); k++) {
        if (vEntities[k]->getId() == id) {
            vEntities.erase(vEntities.begin() + k);
            break;
        }
    }
}