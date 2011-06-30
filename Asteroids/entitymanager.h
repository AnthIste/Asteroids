#ifndef ASTEROIDS_ENTITY_MANAGER_H_
#define ASTEROIDS_ENTITY_MANAGER_H_

#include <vector>
#include "eventsource.h"
#include "entitytypes.h"

class Entity;

class EntityManager: public EventSource {
public:
    EntityManager();
    virtual ~EntityManager();

    void purge();
    void updateAll(int dt);
    const std::vector<Entity*>& getEntities() const { return vEntities; }

    Entity* createEntity(EntityType_t entityType);
    void removeEntity(int id);

private:
    std::vector<Entity*> vEntities;

};

#endif  // ASTEROIDS_ENTITY_MANAGER_H_