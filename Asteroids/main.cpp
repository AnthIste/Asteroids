#include <windows.h>
#include <d3d9.h>

#pragma comment (lib, "d3d9.lib")

// --------------------------------------------------------------------------------------------
// Global Variables
// --------------------------------------------------------------------------------------------
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class

// --------------------------------------------------------------------------------------------
// Function Prototypes
// --------------------------------------------------------------------------------------------
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);    // closes Direct3D and releases memory
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void CenterWindow(HWND hwnd);

// --------------------------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------------------------
const LPWSTR WINDOW_TITLE = L"Our First Windowed Program";
const LPWSTR WINDOW_CLASS = L"WindowClass1";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 500;

// ============================================================================================
// Entry point
// ============================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.lpszClassName = WINDOW_CLASS;

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL,
        WINDOW_CLASS,
        WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hWnd, nCmdShow);
    initD3D(hWnd);

    MSG msg;
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT) {
            break;
        }

        render_frame();
    }

    cleanD3D();

    return msg.wParam;
}

// --------------------------------------------------------------------------------------------
// Window Message Callback
// --------------------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case WM_CREATE: {
            CenterWindow(hWnd);
            return 0;
         } break;

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        } break;

        case WM_KEYDOWN: {
            MessageBox(hWnd, L"Hello!", WINDOW_TITLE, MB_ICONINFORMATION | MB_OK);
        } break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// --------------------------------------------------------------------------------------------
// Helper Functions
// --------------------------------------------------------------------------------------------
void CenterWindow(HWND hwnd)
{
    RECT rc ;
    GetWindowRect (hwnd, &rc) ;

    SetWindowPos(hwnd,
                 0, 
                 (GetSystemMetrics(SM_CXSCREEN) - rc.right)/2,
                 (GetSystemMetrics(SM_CYSCREEN) - rc.bottom)/2,
                 0, 0, SWP_NOZORDER|SWP_NOSIZE );
}

// --------------------------------------------------------------------------------------------
// Direct3D Functions
// --------------------------------------------------------------------------------------------
void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);     // create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp;                // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));          // clear out the struct for use
    d3dpp.Windowed = TRUE;                      // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   // discard old frames
    d3dpp.hDeviceWindow = hWnd;                 // set the window to be used by Direct3D

    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
}

void render_frame(void)
{
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

    d3ddev->BeginScene();

    // do 3D rendering on the back buffer here

    d3ddev->EndScene();

    d3ddev->Present(NULL, NULL, NULL, NULL);
}

void cleanD3D(void)
{
    d3ddev->Release();    // close and release the 3D device
    d3d->Release();    // close and release Direct3D
}