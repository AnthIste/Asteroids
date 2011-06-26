#ifndef ASTEROIDS_BULLETREPRESENTATION_H_
#define ASTEROIDS_BULLETREPRESENTATION_H_

#include "entityrepresentation.h"

class BulletRepresentation: public EntityRepresentation {
public:
    BulletRepresentation();
    virtual ~BulletRepresentation();
    virtual void render(LPDIRECT3DDEVICE9 d3ddev);

private:

};

#endif  // ASTEROIDS_BULLETREPRESENTATION_H_