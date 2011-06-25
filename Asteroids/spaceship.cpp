#include "spaceship.h"

Spaceship::Spaceship() {
}

Spaceship::~Spaceship() {
}

void Spaceship::update(double dt) {
    //setPos(Point2D(getPos().x + getVelocity().getX(), 0.0));

    Point2D newPos = Point2D(getPos().x + (target.x - getPos().x)/6.0, getPos().y + (target.y - getPos().y)/6.0);
    setPos(newPos);
}

void Spaceship::thrust() {
    setVelocity(Vector2D(1.0, 0.0));
}

void Spaceship::unthrust() {
    setVelocity(Vector2D(0.0, 0.0));
}

void Spaceship::setTarget(double x, double y) {
    target = Point2D(x, y);
}