#include "eventsource.h"
#include "eventlistener.h"

EventSource::EventSource() {
}

EventSource::~EventSource() {
}

void EventSource::addListener(EventListener* listener) {
    vListeners.push_back(listener);
}

void EventSource::triggerEvent(int eventId, int param1, int param2, void* extra) {
    for (unsigned int k = 0; k < vListeners.size(); k++) {
        vListeners[k]->onEvent(eventId, param1, param2, extra);
    }
}