#include "inputcontextgame.h"

InputContextGame::InputContextGame() {
}

InputContextGame::~InputContextGame() {
}

void InputContextGame::MapInput(UINT message, WPARAM wParam, LPARAM lParam) {
    // TODO: trigger correct events based on input
    if (message == WM_LBUTTONDOWN) {
        triggerEvent(EVT_SPACESHIP_THRUST, LOWORD(lParam), HIWORD(lParam), 0);
    } else if (message == WM_LBUTTONUP) {
        triggerEvent(EVT_SPACESHIP_UNTHRUST, wParam, lParam, 0);
    } else if (message == WM_MOUSEMOVE) {
        triggerEvent(EVT_SPACESHIP_CHANGETARGET, LOWORD(lParam), HIWORD(lParam), 0);
    } else if (message == WM_KEYDOWN) {
        triggerEvent(EVT_SPACESHIP_RESET, wParam, lParam, 0);
    }
}