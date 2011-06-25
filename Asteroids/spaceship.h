#ifndef ASTEROIDS_SPACESHIP_H_
#define ASTEROIDS_SPACESHIP_H_

#include "entity.h"

class Spaceship: public Entity {
public:
    Spaceship();
    virtual ~Spaceship();

    virtual void update(double dt);
    void setTarget(double x, double y);
    void thrust();
    void unthrust();

private:
    Point2D target;

};

#endif  // ASTEROIDS_SPACESHIP_H_