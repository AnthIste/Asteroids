#include "game.h"
#include "inputcontextgame.h"
#include "spaceship.h"

Game::Game() {
    entityManager.addListener(&entityRepresentationManager);
    inputContext = new InputContextGame();
    inputContext->addListener(this);

    // TODO: initialize all pointers etc to null
    spaceship = 0;

    Reset();
}

Game::~Game() {
    Cleanup();

    if (inputContext) {
        delete inputContext;
        inputContext = 0;
    }
}

void Game::Initialize() {
    // TODO: create all initial entities, reset score, etc
    score = 0;
    lives = 3;
}

void Game::Reset() {
    Cleanup();
    Initialize();
}

void Game::Cleanup() {
    // TODO: iterate through all entities etc and destroy them
}

void Game::Update(int dt) {
    // TODO: update all entities
}

void Game::HandleInput(UINT message, WPARAM wParam, LPARAM lParam) {
    // TODO: map inputs into events based on current context
    // Trigger events to make stuff happen!

    // Replace this with a proper input mapper:
    if (inputContext) {
        inputContext->MapInput(message, wParam, lParam);
    }
}

void Game::Render(LPDIRECT3DDEVICE9 d3ddev) {
    // TODO: render game in correct order (background, asteroids, spaceship, HUD, etc)
    D3DRECT rect = {0+score, 0, 100+score, 100};
    d3ddev->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(50, 40, 100), 1.0f, 0);

    entityRepresentationManager.getRepresentation(spaceship->getId())->render(d3ddev);
}

void Game::onEvent(Event_t eventType, int param1, int param2, void* extra) {
    // TODO: handle all game events here
    // signal new events if necessary

    switch (eventType) {
        case EVT_SPACESHIP_THRUST:
            score++;
            break;

        case EVT_ASTEROID_SPAWN:
            score--;
            break;

        default:
            break;
    }
}