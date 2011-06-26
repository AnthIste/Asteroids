#include "game.h"
#include "inputcontextgame.h"
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"

Game::Game() {
    entityManager.addListener(&entityRepresentationManager);
    inputContext = new InputContextGame();
    inputContext->addListener(this);
    this->addListener(this);

    // TODO: initialize all pointers etc to null
    spaceship = 0;
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
    spaceship->setPos(Point2D(400, 250));
    triggerEvent(EVT_SPACESHIP_SPAWN, 0, 0, spaceship);

    srand(static_cast<unsigned int>(time(0)));
    
    for (int k = 0; k < 3; k++) {
        int x = rand() % 800 + 1;
        int y = rand() % 500 + 1;

        double vx = (rand() % 100)/100.0*3 - 1.5;
        double vy = (rand() % 100)/100.0*3 - 1.5;

        Asteroid* roid = dynamic_cast<Asteroid*>(entityManager.createEntity(ENT_ASTEROID));
        roid->setPos(Point2D(x, y));
        roid->setVelocity(Vector2D(vx, vy));

        triggerEvent(EVT_ASTEROID_SPAWN, 0, 0, roid);

        asteroids.push_back(roid);
    }
}

void Game::Reset() {
    Cleanup();
    Initialize();
}

void Game::Cleanup() {
    entityManager.purge();
    
    // TODO: initialize all pointers etc to null
    spaceship = 0;
    asteroids.clear();
    bullets.clear();
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

    for (unsigned int j = 0; j < bullets.size(); j++) {
        Bullet* bullet = bullets[j];

        for (unsigned int k = 0; k < asteroids.size(); k++) {
            Asteroid* roid = asteroids[k];

            if (bullet->collides(*roid)) {
                triggerEvent(EVT_BULLET_DESTROYED, j, 0, bullet);
                triggerEvent(EVT_ASTEROID_DESTROYED, k, 0, roid);
                break;
            }
        }            
    }

    for (unsigned int k = 0; k < asteroids.size(); k++) {
        Asteroid* roid = asteroids[k];

        if (roid->collides(*spaceship)) {
            triggerEvent(EVT_SPACESHIP_DESTROYED, 0, 0, roid);
            break;
        }

        if (roid->getPos().x > 800) {
            roid->setPos(Point2D(0.0, roid->getPos().y));
        } else if (roid->getPos().x < 0) {
            roid->setPos(Point2D(800, roid->getPos().y));
        } else if (roid->getPos().y > 500) {
            roid->setPos(Point2D(roid->getPos().x, 0.0));
        } else if (roid->getPos().y < 0) {
            roid->setPos(Point2D(roid->getPos().x, 500));
        }
    }
}

void Game::HandleInput(UINT message, WPARAM wParam, LPARAM lParam) {
    if (inputContext) {
        inputContext->MapInput(message, wParam, lParam);
    }
}

void Game::Render(LPDIRECT3DDEVICE9 d3ddev) {
    // TODO: render game in correct order (background, asteroids, spaceship, HUD, etc)
    // TODO: think about how to manage non-entities that also need to be rendered
    
    // Clear the background:
    d3ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Render stars
    // Important to use same seed every frame
    srand(1);
    for (int k = 0; k < 50; k++) {
        int x = rand() % 800 + 1;
        int y = rand() % 500 + 1;

        int sizeSeed = rand() % 100;
        int size = 1;

        if (sizeSeed > 90) {
            size = 3;
        } else if (sizeSeed > 70) {
            size = 2;
        }

        if (size == 3) {
            D3DRECT starPos = {x, y, x+3, y+3};
            d3ddev->Clear(1, &starPos, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
        } else if (size == 2) {
            D3DRECT starPos = {x, y, x+2, y+2};
            d3ddev->Clear(1, &starPos, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
        } else {
            D3DRECT starPos = {x, y, x+1, y+1};
            d3ddev->Clear(1, &starPos, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
        }
    }

    // Render asteroids
    for (unsigned int k = 0; k < asteroids.size(); k++) {
        Asteroid* roid = asteroids[k];

        entityRepresentationManager.getRepresentation(roid->getId())->render(d3ddev);
    }

    // Render the ship
    entityRepresentationManager.getRepresentation(spaceship->getId())->render(d3ddev);

    // Render bullets
    for (unsigned int k = 0; k < bullets.size(); k++) {
        Bullet* bullet = bullets[k];

        if (!spaceship->collides(*bullet)) {
            entityRepresentationManager.getRepresentation(bullet->getId())->render(d3ddev);
        }
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

        case EVT_SPACESHIP_DESTROYED:
            eventSpaceshipDestroyed(param1, param2, extra);
            break;

        case EVT_FIRE_BULLET:
            eventFireBullet(param1, param2, extra);
            break;

        case EVT_ASTEROID_DESTROYED:
            eventAsteroidDestroyed(param1, param2, extra);
            break;

        case EVT_BULLET_DESTROYED:
            eventBulletDestroyed(param1, param2, extra);
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

    triggerEvent(EVT_BULLET_SPAWN, 0, 0, bullet);
}

void Game::eventAsteroidDestroyed(int param1, int param2, void* extra) {
    Asteroid* roid = static_cast<Asteroid*>(extra);
    double x = roid->getX();
    double y = roid->getY();
    int size = roid->getSize();

    asteroids.erase(asteroids.begin() + param1);
    entityManager.removeEntity(roid->getId());

    srand(time(0));
    for (int k = 0; k < size-1; k++) {
        double vx = (rand() % 100)/100.0*3 - 1.5;
        double vy = (rand() % 100)/100.0*3 - 1.5;

        Asteroid* newRoid = dynamic_cast<Asteroid*>(entityManager.createEntity(ENT_ASTEROID));
        newRoid->setPos(Point2D(x, y));
        newRoid->setVelocity(Vector2D(vx, vy));
        newRoid->setSize(size-1);

        triggerEvent(EVT_ASTEROID_SPAWN, newRoid->getX(), newRoid->getY(), newRoid);

        asteroids.push_back(newRoid);
    }
}

void Game::eventBulletDestroyed(int param1, int param2, void* extra) {
    Bullet* bullet = static_cast<Bullet*>(extra);
    bullets.erase(bullets.begin() + param1);
    entityManager.removeEntity(bullet->getId());
}

void Game::eventSpaceshipDestroyed(int param1, int param2, void* extra) {
    entityManager.removeEntity(spaceship->getId());
    spaceship = dynamic_cast<Spaceship*>(entityManager.createEntity(ENT_SPACESHIP));
}