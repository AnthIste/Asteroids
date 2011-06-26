#include "asteroid.h"

Asteroid::Asteroid() {
    setSize(3);
}

Asteroid::~Asteroid() {
}

void Asteroid::update(double dt) {
    // TODO: gently spin the asteroid

    setPos(Point2D(getPos().x + getVelocity().getX(), getPos().y + getVelocity().getY()));
}

void Asteroid::setSize(int size) {
    this->size = size;

    if (size >= 3) {
       this->size = 3;
        setHitRadius(30);
    } else if (size >= 2) {
        setHitRadius(20);
    } else if (size >= 1) {
        setHitRadius(10);
    } else {
        this->size = 1;
        setHitRadius(10);
    }
}