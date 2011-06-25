#ifndef ASTEROIDS_SPACESHIP_H_
#define ASTEROIDS_SPACESHIP_H_

#include "entity.h"

class Spaceship: public Entity {
public:
    Spaceship();
    virtual ~Spaceship();

    virtual void update(double dt);
    void thrust();
    void unthrust();

private:

};

#endif  // ASTEROIDS_SPACESHIP_H_