#ifndef ASTEROIDS_SPACESHIP_H_
#define ASTEROIDS_SPACESHIP_H_

#include "entity.h"

class Spaceship: public Entity {
public:
    Spaceship();
    virtual ~Spaceship();

    virtual void update(int dt);
    void setVelocity(const Vector2D& velocity) { m_velocity = velocity; }
    Vector2D getVelocity() const { return m_velocity; }
    void thrust();
    void unthrust();
    void startTurn(int direction);
    void stopTurn();

    double getRotationRadians() const { return rotationRadians; }
    double getRotationTargetRadians() const { return rotationTargetRadians; }

private:
    Vector2D m_velocity;
    int turnDirection;
    double rotationRadians;
    double rotationTargetRadians;
    bool bThrust;

};

#endif  // ASTEROIDS_SPACESHIP_H_