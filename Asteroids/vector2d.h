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
    void setXY(double x, double y);
    void setPolar(double magnitude, double rotation);
    
    void add(const Vector2D& rhs);
    double getMagnitude() const;
    double getDirectionRadians() const;
    void rotateBy(double rotationDeltaRadians);
    void setRotationRadians(double rotationRadians);
    void setMagnitude(double magnitude);
    
private:
    double x;
    double y;

};

#endif  // ASTEROIDS_VECTOR2D_H_