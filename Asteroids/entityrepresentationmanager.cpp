#include "entityrepresentationmanager.h"
#include "entityrepresentation.h"

EntityRepresentationManager::EntityRepresentationManager() {
}

EntityRepresentationManager::~EntityRepresentationManager() {
    // TODO: this should not be necessary if all events are handled correctly
    for (unsigned int k = 0; k < mEntityRepresentations.size(); k++) {
        delete mEntityRepresentations[k];
    }
}

void EntityRepresentationManager::onEvent(Event_t eventType, int param1, int param2, void* extra) {
    // TODO: check for entity create/delete and map representation accordingly
}

EntityRepresentation* EntityRepresentationManager::getRepresentation(int id) {
    return mEntityRepresentations[id];
}