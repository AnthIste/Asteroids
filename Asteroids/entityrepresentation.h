#ifndef ASTEROIDS_ENTITYREPRESENTATION_H_
#define ASTEROIDS_ENTITYREPRESENTATION_H_

#include <d3d9.h>

class EntityRepresentation {
public:
    EntityRepresentation();
    virtual ~EntityRepresentation();

    virtual void render(LPDIRECT3DDEVICE9 d3ddev) = 0;

private:
    double x;
    double y;
    // TODO: add other info
    // double width
    // double height
    // Sprite* p_sprite;

};

#endif  // ASTEROIDS_ENTITYREPRESENTATION_H_