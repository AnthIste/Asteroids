#ifndef ASTEROIDS_ENTITYREPRESENTATION_H_
#define ASTEROIDS_ENTITYREPRESENTATION_H_

#include <d3d9.h>
#include "entity.h"

class EntityRepresentation {
public:
    EntityRepresentation();
    virtual ~EntityRepresentation();

    void setEntity(Entity* entity) { this->entity = entity; }
    Entity* getEntity() const { return entity; }
    virtual void render(LPDIRECT3DDEVICE9 d3ddev) = 0;

private:
    Entity* entity;

    double x;
    double y;
    // TODO: add other info
    // double width
    // double height
    // Sprite* p_sprite;

};

#endif  // ASTEROIDS_ENTITYREPRESENTATION_H_