#include "inputcontextgame.h"

InputContextGame::InputContextGame() {
}

InputContextGame::~InputContextGame() {
}

void InputContextGame::MapInput(UINT message, WPARAM wParam, LPARAM lParam) {
    // TODO: trigger correct events based on input
    if (message == WM_KEYDOWN) {
        triggerEvent(EVT_SPACESHIP_THRUST, wParam, lParam, 0);
    } else if (message == WM_LBUTTONDOWN) {
        triggerEvent(EVT_ASTEROID_SPAWN, wParam, lParam, 0);
    }
}