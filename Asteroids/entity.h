#ifndef ASTEROIDS_ENTITY_H_
#define ASTEROIDS_ENTITY_H_

#include "point2d.h"
#include "vector2d.h"

class Entity {
public:
    Entity() : m_hitRadius(0.0) {}
    virtual ~Entity() {}

    void setHitRadius(double hitRadius) { m_hitRadius = hitRadius; }
    void setPos(const Point2D& pos) { m_pos = pos; }
    void setVelocity(const Vector2D& velocity) { m_velocity = velocity; }
    Point2D getPos() const { return m_pos; }
    Vector2D getVelocity() const { return m_velocity; }

    void update(double dt);
    bool collides(const Entity& ent);

    // TODO: create interface for entities to signal events

private:
    Point2D m_pos;
    Vector2D m_velocity;
    double m_hitRadius;

};

#endif  // ASTEROIDS_ENTITY_H