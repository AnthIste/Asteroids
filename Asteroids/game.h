#ifndef ASTEROIDS_GAME_H_
#define ASTEROIDS_GAME_H_

#include <windows.h>
#include <time.h>
#include <d3d9.h>
#include <vector>
#include "eventsource.h"
#include "eventlistener.h"
#include "entitymanager.h"
#include "entityrepresentationmanager.h"

class InputContext;
class Spaceship;
class Bullet;
class Asteroid;

class Game: public EventSource, public EventListener {
public:
    Game();
    ~Game();

    void Initialize();
    void Reset();
    void Cleanup();

    void Update(int dt);
    void HandleInput(UINT message, WPARAM wParam, LPARAM lParam);
    void Render(LPDIRECT3DDEVICE9 d3ddev);
    virtual void onEvent(Event_t eventType, int param1, int param2, void* extra);

protected:
    void eventFireBullet(int param1, int param2, void* extra);
    void eventAsteroidDestroyed(int param1, int param2, void* extra);
    void eventBulletDestroyed(int param1, int param2, void* extra);

private:
    EntityManager entityManager;
    EntityRepresentationManager entityRepresentationManager;
    InputContext* inputContext;

    // ----------------------------------------------------
    // Game State
    // ----------------------------------------------------
    int score;
    int lives;
    Spaceship* spaceship;
    std::vector<Bullet*> bullets;
    std::vector<Asteroid*> asteroids;

};

#endif  // ASTEROIDS_GAME_H_