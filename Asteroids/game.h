#ifndef ASTEROIDS_GAME_H_
#define ASTEROIDS_GAME_H_

#include <windows.h>
#include <d3d9.h>
#include <vector>
#include "eventlistener.h"
#include "entitymanager.h"
#include "entityrepresentationmanager.h"

class InputContext;
class Spaceship;

// TODO: link game events to input controller
class Game: public EventListener {
public:
    Game();
    ~Game();

    void Initialize();
    void Reset();
    void Cleanup();

    void Update(int dt);
    void HandleInput(UINT message, WPARAM wParam, LPARAM lParam);
    void Render(LPDIRECT3DDEVICE9 d3ddev);
    virtual void onEvent(int id, int param1, int param2, void* extra);

private:
    EntityManager entityManager;
    EntityRepresentationManager entityRepresentationManager;
    InputContext* inputContext;

    int score;
    int lives;
    Spaceship* spaceship;
    // FIXME: reference to other game objects here

};

#endif  // ASTEROIDS_GAME_H_