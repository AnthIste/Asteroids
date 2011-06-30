#include "spaceship.h"
#include <cmath>
#include <math.h>

#define PI 3.14159265

Spaceship::Spaceship() {
    turnDirection = 0;
    rotationRadians = m_velocity.getDirectionRadians();
    rotationTargetRadians = rotationRadians;
    bThrust = false;
    setHitRadius(20);
}

Spaceship::~Spaceship() {
}

void Spaceship::update(int dt) {
    // Rotate spaceship
    double turnFactor = 10.0 + m_velocity.getMagnitude()*3;

    if (turnDirection == -1) {
        rotationTargetRadians -= 2 * PI / 360 * 60/turnFactor;
    } else if (turnDirection == 1) {
        rotationTargetRadians += 2 * PI / 360 * 60/turnFactor;
    }

    //turnFactor *= (bThrust ? 0.99 : 1.1);
    double rotationDelta = (rotationTargetRadians - rotationRadians)/turnFactor;
    rotationRadians += rotationDelta;

    // dampen current velocity
    m_velocity.setMagnitude(m_velocity.getMagnitude() * 0.995);

    // accellerate in current direction
    if (bThrust) {
        Vector2D newVelocity;
        newVelocity.setPolar(0.1, rotationRadians);

        m_velocity.add(newVelocity);

        if (m_velocity.getMagnitude() > 6.0) {
            m_velocity.setPolar(6.0, m_velocity.getDirectionRadians());
        }

        m_velocity.setPolar(m_velocity.getMagnitude(), m_velocity.getDirectionRadians() + rotationDelta);
    }
    
    // update position
    setPos(Point2D(getPos().x + getVelocity().getX(), getPos().y + getVelocity().getY()));
}

void Spaceship::thrust() {
    bThrust = true;
}

void Spaceship::unthrust() {
    bThrust = false;
}

void Spaceship::startTurn(int direction) {
    if (direction == -1) {
        // left
        turnDirection = -1;
    } else if (direction == 1) {
        // right
        turnDirection = 1;
    } else {
        turnDirection = 0;
    }
}

void Spaceship::stopTurn() {
    turnDirection = 0;
}