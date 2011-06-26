#include "inputcontextgame.h"

InputContextGame::InputContextGame() {
}

InputContextGame::~InputContextGame() {
}

void InputContextGame::MapInput(UINT message, WPARAM wParam, LPARAM lParam) {
    // TODO: trigger correct events based on input
    if (message == WM_KEYDOWN) {
        if (wParam == VK_LEFT) {
            triggerEvent(EVT_SPACESHIP_STARTTURN, -1, 0, 0);
        } else if (wParam == VK_RIGHT) {
            triggerEvent(EVT_SPACESHIP_STARTTURN, 1, 0, 0);
        } else if (wParam == VK_UP) {
            triggerEvent(EVT_SPACESHIP_THRUST, LOWORD(lParam), HIWORD(lParam), 0);
        } else if (wParam == VK_SPACE) {
            triggerEvent(EVT_FIRE_BULLET, 0, 0, 0);
        } else {
            triggerEvent(EVT_SPACESHIP_RESET, wParam, lParam, 0);
        }
    } else if (message == WM_KEYUP) {
        if (wParam == VK_LEFT || wParam == VK_RIGHT) {
            triggerEvent(EVT_SPACESHIP_STOPTURN, 0, 0, 0);
        } else if (wParam == VK_UP) {
            triggerEvent(EVT_SPACESHIP_UNTHRUST, wParam, lParam, 0);
        }
    }
}