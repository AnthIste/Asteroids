#include "bullet.h"

Bullet::Bullet() {
    timeAlive = 0;
    timeExpire = 0;
}

Bullet::~Bullet() {
}

void Bullet::update(int dt) {
    timeAlive += dt;
    setPos(Point2D(getPos().x + getVelocity().getX(), getPos().y + getVelocity().getY()));
}

bool Bullet::hasExpired() {
    return (timeExpire != 0 && timeAlive > timeExpire);
}