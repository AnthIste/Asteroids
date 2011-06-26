#ifndef ASTEROIDS_ASTEROIDREPRESENTATION_H_
#define ASTEROIDS_ASTEROIDREPRESENTATION_H_

#include "entityrepresentation.h"

class AsteroidRepresentation: public EntityRepresentation {
public:
    AsteroidRepresentation();
    virtual ~AsteroidRepresentation();
    virtual void render(LPDIRECT3DDEVICE9 d3ddev);

private:

};

#endif  // ASTEROIDS_ASTEROIDREPRESENTATION_H_