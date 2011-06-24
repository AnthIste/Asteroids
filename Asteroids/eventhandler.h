#ifndef ASTEROIDS_EVENTHANDLER_H_
#define ASTEROIDS_EVENTHANDLER_H_

class EventHandler {
public:
    EventHandler();
    virtual ~EventHandler();

    void handleEvent(int id, int param1, int param2, void* extra);
    virtual void onEvent(int id, int param1, int param2, void* extra);

private:
};

#endif  // ASTEROIDS_EVENTHANDLER_H_