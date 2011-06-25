#ifndef ASTEROIDS_SPACESHIPREPRESENTATION_H_
#define ASTEROIDS_SPACESHIPREPRESENTATION_H_

#include "entityrepresentation.h"

class SpaceshipRepresentation: public EntityRepresentation {
public:
    SpaceshipRepresentation();
    virtual ~SpaceshipRepresentation();
    virtual void render(LPDIRECT3DDEVICE9 d3ddev);

private:

};

#endif  // ASTEROIDS_SPACESHIPREPRESENTATION_H_