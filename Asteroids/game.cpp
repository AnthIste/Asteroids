#include "game.h"
#include "inputcontextgame.h"
#include "spaceship.h"
#include "bullet.h"

Game::Game() {
    entityManager.addListener(&entityRepresentationManager);
    inputContext = new InputContextGame();
    inputContext->addListener(this);
    this->addListener(this);

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

    spaceship = dynamic_cast<Spaceship*>(entityManager.createEntity(ENT_SPACESHIP));
}

void Game::Reset() {
    Cleanup();
    Initialize();
}

void Game::Cleanup() {
    entityManager.purge();
    
    // TODO: initialize all pointers etc to null
    spaceship = 0;
}

void Game::Update(int dt) {
    entityManager.updateAll(dt);

    // FIXME: set playing area size
    if (spaceship->getPos().x > 800) {
        spaceship->setPos(Point2D(0.0, spaceship->getPos().y));
    } else if (spaceship->getPos().x < 0) {
        spaceship->setPos(Point2D(800, spaceship->getPos().y));
    } else if (spaceship->getPos().y > 500) {
        spaceship->setPos(Point2D(spaceship->getPos().x, 0.0));
    } else if (spaceship->getPos().y < 0) {
        spaceship->setPos(Point2D(spaceship->getPos().x, 500));
    } 
}

void Game::HandleInput(UINT message, WPARAM wParam, LPARAM lParam) {
    if (inputContext) {
        inputContext->MapInput(message, wParam, lParam);
    }
}

void Game::Render(LPDIRECT3DDEVICE9 d3ddev) {
    // TODO: render game in correct order (background, asteroids, spaceship, HUD, etc)
    D3DRECT rect = {0+score, 0, 100+score, 100};
    d3ddev->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(50, 40, 100), 1.0f, 0);

    entityRepresentationManager.getRepresentation(spaceship->getId())->render(d3ddev);

    for (int k = 0; k < bullets.size(); k++) {
        Bullet* bullet = bullets[k];
        entityRepresentationManager.getRepresentation(bullet->getId())->render(d3ddev);
    }
}

void Game::onEvent(Event_t eventType, int param1, int param2, void* extra) {
    switch (eventType) {
        case EVT_SPACESHIP_THRUST:
            spaceship->thrust();
            break;

        case EVT_SPACESHIP_UNTHRUST:
            spaceship->unthrust();
            break;

        case EVT_SPACESHIP_RESET:
            spaceship->setPos(Point2D(0.0, 0.0));
            break;

        case EVT_SPACESHIP_STARTTURN:
            spaceship->startTurn(param1);
            break;

        case EVT_SPACESHIP_STOPTURN:
            spaceship->stopTurn();
            break;

        case EVT_FIRE_BULLET:
            eventFireBullet(param1, param2, extra);
            break;

        default:
            break;
    }
}

void Game::eventFireBullet(int param1, int param2, void* extra) {
    Point2D sourcePos = spaceship->getPos();
    Vector2D velocity;
    velocity.setPolar(9.0, spaceship->getRotationRadians());

    Bullet* bullet = dynamic_cast<Bullet*>(entityManager.createEntity(ENT_BULLET));
    bullet->setPos(sourcePos);
    bullet->setVelocity(velocity);

    bullets.push_back(bullet);
}