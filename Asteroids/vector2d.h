#ifndef ASTEROIDS_VECTOR2D_H_
#define ASTEROIDS_VECTOR2D_H_

class Vector2D {
public:
    Vector2D() : x(0.0), y(0.0) {}
    Vector2D(double x, double y) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void set(double x, double y) { this->x = x; this->y = y; }
    
    void add(const Vector2D& rhs);
    double getMagnitude() const;
    double getDirection() const;
    
private:
    double x;
    double y;

};

#endif  // ASTEROIDS_VECTOR2D_H_