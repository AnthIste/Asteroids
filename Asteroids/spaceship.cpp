#include "spaceship.h"

Spaceship::Spaceship() {
}

Spaceship::~Spaceship() {
}

void Spaceship::update(double dt) {
    setPos(Point2D(getPos().x + getVelocity().getX(), 0.0));
}

void Spaceship::thrust() {
    setVelocity(Vector2D(1.0, 0.0));
}

void Spaceship::unthrust() {
    setVelocity(Vector2D(0.0, 0.0));
}