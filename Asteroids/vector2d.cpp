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