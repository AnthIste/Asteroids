#ifndef ASTEROIDS_ENGINE_H_
#define ASTEROIDS_ENGINE_H_

#include <windows.h>
#include <d3d9.h>
#include <map>

#pragma comment (lib, "d3d9.lib")

const LPWSTR WINDOW_TITLE = L"Engine";
const LPWSTR WINDOW_CLASS = L"WCOurEngine";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 500;

class Engine {
public:
    Engine();
    ~Engine();

    void initialize(HINSTANCE hInstance, int width, int height, bool bFullscreen);
    void run();
    void cleanup();

private:
    void initD3D(HWND hWnd, int width, int height, bool bFullscreen);
    void render_frame();
    void cleanD3D();
    void CenterWindow(HWND hwnd);
    LRESULT CALLBACK onWindowEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    HWND hWnd;
    LPDIRECT3D9 d3d;            // the pointer to our Direct3D interface
    LPDIRECT3DDEVICE9 d3ddev;   // the pointer to the device class

    static std::map<HWND, Engine*> wndProcMap;

};

#endif  // ASTEROIDS_ENGINE_H_