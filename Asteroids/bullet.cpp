#include "bullet.h"

Bullet::Bullet() {
    timeAlive = 0.0;
}

Bullet::~Bullet() {
}

void Bullet::update(double dt) {
    timeAlive += dt;

    // TODO: check if bullet expires

    setPos(Point2D(getPos().x + getVelocity().getX(), getPos().y + getVelocity().getY()));
}