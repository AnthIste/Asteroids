#ifndef ASTEROIDS_INPUT_CONTEXT_H_
#define ASTEROIDS_INPUT_CONTEXT_H_

#include <windows.h>
#include "eventsource.h"

class InputContext: public EventSource {
public:
    InputContext() {}
    ~InputContext() {}

    virtual void MapInput(UINT message, WPARAM wParam, LPARAM lParam) = 0;

private:
};

#endif  // ASTEROIDS_INPUT_CONTEXT_H_