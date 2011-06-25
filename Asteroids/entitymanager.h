#ifndef ASTEROIDS_ENTITY_MANAGER_H_
#define ASTEROIDS_ENTITY_MANAGER_H_

#include <vector>
#include "eventsource.h"

class Entity;

class EntityManager: public EventSource {
public:
    EntityManager();
    virtual ~EntityManager();

    void addEntity(Entity* entity);
    void removeEntity(int id);
    const std::vector<Entity*>& getEntities() const { return vEntities; }

private:
    std::vector<Entity*> vEntities;

};

#endif  // ASTEROIDS_ENTITY_MANAGER_H_