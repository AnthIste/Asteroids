#ifndef ASTEROIDS_BULLET_H_
#define ASTEROIDS_BULLET_H_

#include "entity.h"

class Bullet: public Entity {
public:
    Bullet();
    virtual ~Bullet();

    void setVelocity(const Vector2D& velocity) { m_velocity = velocity; }
    Vector2D getVelocity() const { return m_velocity; }

    virtual void update(double dt);

private:
    Vector2D m_velocity;
    double timeAlive;
};

#endif  // ASTEROIDS_BULLET_H_