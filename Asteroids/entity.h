#ifndef ASTEROIDS_ENTITY_H_
#define ASTEROIDS_ENTITY_H_

#include "eventsource.h"
#include "point2d.h"
#include "vector2d.h"
#include "entitytypes.h"

class Entity: public EventSource {
public:
    Entity() : m_hitRadius(0.0), m_id(ID_SEED++) {}
    virtual ~Entity() {}

    void setHitRadius(double hitRadius) { m_hitRadius = hitRadius; }
    double getHitRadius() const { return m_hitRadius; }
    void setPos(const Point2D& pos) { m_pos = pos; }
    Point2D getPos() const { return m_pos; }
    double getX() const { return m_pos.x; }
    double getY() const { return m_pos.y; }
    int getId() const { return m_id; }
    bool collides(const Entity& ent);

    virtual void update(int dt) = 0;

private:
    Point2D m_pos;
    double m_hitRadius;
    int m_id;

    static int ID_SEED;

};

#endif  // ASTEROIDS_ENTITY_H