#ifndef ASTEROIDS_POINT2D_H_
#define ASTEROIDS_POINT2D_H_

struct Point2D {
    Point2D() : x(0.0), y(0.0) {}
    Point2D(double x, double y) : x(x), y(y) {}

    double x;
    double y;
};

#endif  // ASTEROIDS_POINT2D_H_