#ifndef ASTEROIDS_EVENTLISTENER_H_
#define ASTEROIDS_EVENTLISTENER_H_

class EventListener {
public:
    EventListener();
    virtual ~EventListener();

    virtual void onEvent(int id, int param1, int param2, void* extra) = 0;

private:

};

#endif  // ASTEROIDS_EVENTLISTENER_H_