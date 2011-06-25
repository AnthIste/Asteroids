#ifndef ASTEROIDS_INPUTCONTEXTGAME_H_
#define ASTEROIDS_INPUTCONTEXTGAME_H_

#include "inputcontext.h"

class InputContextGame: public InputContext {
public:
    InputContextGame();
    ~InputContextGame();

    virtual void MapInput(UINT message, WPARAM wParam, LPARAM lParam);

private:

};

#endif  // ASTEROIDS_INPUTCONTEXTGAME_H_