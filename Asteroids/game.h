#ifndef ASTEROIDS_GAME_H_
#define ASTEROIDS_GAME_H_

#include <d3d9.h>
#include <vector>
#include "entitymanager.h"
#include "entityrepresentationmanager.h"

class Spaceship;

// TODO: link game events to input controller
class Game {
public:
    Game();
    ~Game();

    void Initialize();
    void Reset();
    void Cleanup();

    void Update(int dt);
    void Render(LPDIRECT3DDEVICE9 d3ddev);

private:
    EntityManager entityManager;
    EntityRepresentationManager entityRepresentationManager;

    Spaceship* spaceship;
    // FIXME: reference to other game objects here

};

#endif  // ASTEROIDS_GAME_H_