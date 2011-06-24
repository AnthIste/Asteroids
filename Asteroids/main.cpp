#include <windows.h>
#include "engine.h"

// ============================================================================================
// Entry point
// ============================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Engine engine;
    //engine.initialize(hInstance, 800, 500, false);
    engine.initialize(hInstance, 1600, 900, true);
    engine.run();
    engine.cleanup();

    return 0;
}