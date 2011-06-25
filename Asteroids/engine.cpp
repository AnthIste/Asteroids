#include "engine.h"
#include "game.h"

std::map<HWND, Engine*> Engine::wndProcMap;

Engine::Engine() {
    hWnd = 0;
    d3d = 0;
    d3ddev = 0;
    game = 0;
}

Engine::~Engine() {
    if (game) {
        delete game;
    }
}

void Engine::initialize(HINSTANCE hInstance, int width, int height, bool bFullscreen) {
    game = new Game();

    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    if (!bFullscreen) {
        wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    }
    wc.lpszClassName = WINDOW_CLASS;

    BOOLEAN bSuccess = RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL,
        WINDOW_CLASS,
        WINDOW_TITLE,
        (bFullscreen ? WS_EX_TOPMOST | WS_POPUP : WS_OVERLAPPEDWINDOW),
        0,
        0,
        width,
        height,
        NULL,
        NULL,
        hInstance,
        NULL);

    wndProcMap[hWnd] = this;

    ShowWindow(hWnd, TRUE);
    initD3D(hWnd, width, height, bFullscreen);
}

void Engine::run() {
    game->Initialize();

    MSG msg;
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT) {
            break;
        }

        // TODO: get dt
        game->Update(0);
        render_frame();
    }
}

void Engine::cleanup() {
    wndProcMap[hWnd] = 0;
    cleanD3D();
}

void Engine::initD3D(HWND hWnd, int width, int height, bool bFullscreen) {
    d3d = Direct3DCreate9(D3D_SDK_VERSION);     // create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp;                // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));          // clear out the struct for use
    d3dpp.Windowed = !bFullscreen;              // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   // discard old frames
    d3dpp.hDeviceWindow = hWnd;                 // set the window to be used by Direct3D
    if (bFullscreen) {
        d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
        d3dpp.BackBufferWidth = width;          // set the width of the buffer
        d3dpp.BackBufferHeight = height;        // set the height of the buffer
    }

    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
}

void Engine::render_frame() {
    if (d3ddev) {
        d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

        d3ddev->BeginScene();

        game->Render(d3ddev);

        d3ddev->EndScene();

        d3ddev->Present(NULL, NULL, NULL, NULL);
    }
}

void Engine::cleanD3D() {
    if (d3ddev) {
        d3ddev->Release();
    }
    if (d3d) {
        d3d->Release();
    }
}

void Engine::CenterWindow(HWND hwnd) {
    RECT rc ;
    GetWindowRect (hwnd, &rc) ;

    SetWindowPos(hwnd,
                 0, 
                 (GetSystemMetrics(SM_CXSCREEN) - rc.right)/2,
                 (GetSystemMetrics(SM_CYSCREEN) - rc.bottom)/2,
                 0, 0, SWP_NOZORDER|SWP_NOSIZE );
}

LRESULT CALLBACK Engine::onWindowEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE: {
            //CenterWindow(hWnd);
            return 0;
         } break;

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    game->HandleInput(message, wParam, lParam);

    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK Engine::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (wndProcMap[hWnd]) {
        return wndProcMap[hWnd]->onWindowEvent(hWnd, message, wParam, lParam);
    } else {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}