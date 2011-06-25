#include "inputcontextgame.h"

InputContextGame::InputContextGame() {
}

InputContextGame::~InputContextGame() {
}

void InputContextGame::MapInput(UINT message, WPARAM wParam, LPARAM lParam) {
    // TODO: trigger correct events based on input
    if (message == WM_KEYDOWN) {
        triggerEvent(0, wParam, lParam, 0);
    } else if (message == WM_LBUTTONDOWN) {
        triggerEvent(1, wParam, lParam, 0);
    }
}