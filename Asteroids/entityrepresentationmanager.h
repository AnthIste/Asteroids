#ifndef ASTEROIDS_ENTITYREPRESENTATIONMANAGER_H_
#define ASTEROIDS_ENTITYREPRESENTATIONMANAGER_H_

#include <map>
#include "eventlistener.h"
#include "entityrepresentation.h"

class EntityRepresentationManager: public EventListener {
public:
    EntityRepresentationManager();
    virtual ~EntityRepresentationManager();

    virtual void onEvent(Event_t eventType, int param1, int param2, void* extra);
    EntityRepresentation* getRepresentation(int id);

protected:
    EntityRepresentation* createRepresentation(EntityType_t entityType);

private:
    std::map<int, EntityRepresentation*> mEntityRepresentations;

};

#endif  // ASTEROIDS_ENTITYREPRESENTATIONMANAGER_H_