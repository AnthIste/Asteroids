#ifndef ASTEROIDS_ASTEROID_H_
#define ASTEROIDS_ASTEROID_H_

#include "entity.h"

class Asteroid: public Entity {
public:
    Asteroid();
    virtual ~Asteroid();

    void setVelocity(const Vector2D& velocity) { m_velocity = velocity; }
    Vector2D getVelocity() const { return m_velocity; }
    void setSpin(double spin) { this->spin = spin; }
    double getSpin() const { return spin; }
    int getSize() const { return size; }

    virtual void update(double dt);
    void setSize(int size);

private:
    Vector2D m_velocity;
    double spin;
    double rotation;
    int size;

};

#endif  // ASTEROIDS_ASTEROID_H_