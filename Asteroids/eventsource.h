#ifndef ASTEROIDS_EVENTSOURCE_H_
#define ASTEROIDS_EVENTSOURCE_H_

#include <vector>

class EventListener;

class EventSource {
public:
    EventSource();
    virtual ~EventSource();

    void addListener(EventListener* listener);

protected:
    void triggerEvent(int eventId, int param1, int param2, void* extra);

private:
    std::vector<EventListener*> vListeners;

};

#endif  // ASTEROIDS_EVENTSOURCE_H_