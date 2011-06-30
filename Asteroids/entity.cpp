#include "entity.h"
#include <cmath>

int Entity::ID_SEED = 0;

bool Entity::collides(const Entity& ent) {
    return sqrt(pow(ent.getX() - getX(), 2) + pow(ent.getY() - getY(), 2)) < getHitRadius() + ent.getHitRadius();
}