#include "vector2d.h"
#include <math.h>

void Vector2D::add(const Vector2D& rhs) {
    x += rhs.x;
    y += rhs.y;
}

double Vector2D::getMagnitude() const {
    return sqrt(x*x + y*y);
}

double Vector2D::getDirectionRadians() const {
    return atan2(y, x);
}

void Vector2D::setXY(double x, double y) {
    this->x = x;
    this->y = y;
}

void Vector2D::setPolar(double magnitude, double rotation) {
    x = magnitude * cos(rotation);
    y = magnitude * sin(rotation);
}

void Vector2D::rotateBy(double rotationDeltaRadians) {
    setPolar(getMagnitude(), getDirectionRadians() + rotationDeltaRadians);
}

void Vector2D::setRotationRadians(double rotationRadians) {
    setPolar(getMagnitude(), rotationRadians);
}

void Vector2D::setMagnitude(double magnitude) {
    setPolar(magnitude, getDirectionRadians());
}