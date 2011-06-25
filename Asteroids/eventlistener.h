#ifndef ASTEROIDS_EVENTLISTENER_H_
#define ASTEROIDS_EVENTLISTENER_H_

#include "events.h"

class EventListener {
public:
    EventListener() {}
    virtual ~EventListener() {}

    virtual void onEvent(Event_t eventType, int param1, int param2, void* extra) = 0;

private:

};

#endif  // ASTEROIDS_EVENTLISTENER_H_