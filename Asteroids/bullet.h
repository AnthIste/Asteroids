#ifndef ASTEROIDS_BULLET_H_
#define ASTEROIDS_BULLET_H_

#include "entity.h"

class Bullet: public Entity {
public:
    Bullet();
    virtual ~Bullet();

    void setVelocity(const Vector2D& velocity) { m_velocity = velocity; }
    Vector2D getVelocity() const { return m_velocity; }
    void setTimeExpire(int timeExpire) { this->timeExpire = timeExpire; }
    int getTimeExpire() const { return timeExpire; }

    virtual void update(int dt);
    bool hasExpired();

private:
    Vector2D m_velocity;
    int timeAlive;
    int timeExpire;

};

#endif  // ASTEROIDS_BULLET_H_