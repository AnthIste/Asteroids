#include "game.h"

Game::Game() {
    entityManager.addListener(&entityRepresentationManager);

    // TODO: initialize all pointers etc to null
    spaceship = 0;

    Reset();
}

Game::~Game() {
    Cleanup();
}

void Game::Initialize() {
    // TODO: create all initial entities, reset score, etc
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

void Game::Render(LPDIRECT3DDEVICE9 d3ddev) {
    // TODO: render game in correct order (background, asteroids, spaceship, HUD, etc)
}