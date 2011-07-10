#include "game.h"
#include "inputcontextgame.h"
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include "starfield.h"

Game::Game() {
    entityManager.addListener(&entityRepresentationManager);
    inputContext = new InputContextGame();
    inputContext->addListener(this);
    this->addListener(this);

    spaceship = 0;
    score = 0;
    lives = 0;
    starfield = 0;
}

Game::~Game() {
    Cleanup();

    if (inputContext) {
        delete inputContext;
        inputContext = 0;
    }
}

void Game::Initialize() {
    // Initialize game lives/score to default values
    score = 0;
    lives = 3;

    // FIXME: use proper game dimensions for starting position
    // Create initial spaceship
    spaceship = dynamic_cast<Spaceship*>(entityManager.createEntity(ENT_SPACESHIP));
    spaceship->setPos(Point2D(400, 250));
    triggerEvent(EVT_SPACESHIP_SPAWN, 0, 0, spaceship);

    spawnAsteroids(4);

    // Initialize the starry background
    starfield = new Starfield(800, 500);
}

void Game::Reset() {
    Cleanup();
    Initialize();
}

void Game::Cleanup() {
    // This will free memory allocated by all entities
    entityManager.purge();
    
    // TODO: initialize all pointers etc to null
    spaceship = 0;
    delete starfield;
    starfield = 0;
    asteroids.clear();
    bullets.clear();
}

void Game::Update(int dt) {
    // Update all entities with current time delta
    entityManager.updateAll(dt);

    // FIXME: set playing area size
    // Loop spaceship over screen edges
    loopEntity(spaceship);

    // Update bullets and
    // Check for bullet collisions and
    // Remove expired bullets
    for (unsigned int j = 0; j < bullets.size(); j++) {
        Bullet* bullet = bullets[j];

        if (bullet->hasExpired()) {
            triggerEvent(EVT_BULLET_DESTROYED, j, 0, bullet);
        } else {
            for (unsigned int k = 0; k < asteroids.size(); k++) {
                Asteroid* roid = asteroids[k];

                if (bullet->collides(*roid)) {
                    triggerEvent(EVT_BULLET_DESTROYED, j, 0, bullet);
                    triggerEvent(EVT_ASTEROID_DESTROYED, k, 0, roid);
                    break;
                }
            }
        }
    }

    // Loop asteroids past edges of screen and
    // Check for asteroid/spaceship collisions
    for (unsigned int k = 0; k < asteroids.size(); k++) {
        Asteroid* roid = asteroids[k];

        if (roid->collides(*spaceship)) {
            triggerEvent(EVT_SPACESHIP_DESTROYED, 0, 0, roid);
        }

        loopEntity(roid);
    }

    // Scroll the background based on the current ship velocity
    Vector2D shipVelocity = spaceship->getVelocity();
    starfield->scroll(shipVelocity.getX() * 0.3, shipVelocity.getY() * 0.3);
}

void Game::HandleInput(UINT message, WPARAM wParam, LPARAM lParam) {
    if (inputContext) {
        inputContext->MapInput(message, wParam, lParam);
    }
}

void Game::Render(LPDIRECT3DDEVICE9 d3ddev) {
    // TODO: think about how to manage non-entities that also need to be rendered
    
    // Clear the background:
    d3ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Render stars
    starfield->render(d3ddev);

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

void Game::spawnAsteroids(int numAsteroids) {
    // Create asteroids in random positions with random velocities
    srand(static_cast<unsigned int>(time(0)));
    
    for (int k = 0; k < numAsteroids; k++) {
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

// FIXME: use proper game dimension
void Game::loopEntity(Entity* entity) {
    if (entity->getPos().x > 800) {
        entity->setPos(Point2D(0.0, entity->getPos().y));
    } else if (entity->getPos().x < 0) {
        entity->setPos(Point2D(800, entity->getPos().y));
    } else if (entity->getPos().y > 500) {
        entity->setPos(Point2D(entity->getPos().x, 0.0));
    } else if (entity->getPos().y < 0) {
        entity->setPos(Point2D(entity->getPos().x, 500));
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

        case EVT_ASTEROIDS_RESET:
            eventAsteroidsReset(param1, param2, extra);
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
    bullet->setTimeExpire(1000);

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
    for (int k = 0; k < size+1 && size != 1; k++) {
        double vx = (rand() % 100)/100.0*3 - 1.5;
        double vy = (rand() % 100)/100.0*3 - 1.5;

        Asteroid* newRoid = dynamic_cast<Asteroid*>(entityManager.createEntity(ENT_ASTEROID));
        newRoid->setPos(Point2D(x, y));
        newRoid->setVelocity(Vector2D(vx, vy));
        newRoid->setSize(size-1);

        triggerEvent(EVT_ASTEROID_SPAWN, newRoid->getX(), newRoid->getY(), newRoid);

        asteroids.push_back(newRoid);
    }

    if (asteroids.empty()) {
        triggerEvent(EVT_ASTEROIDS_RESET,0, 0, 0);
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

void Game::eventAsteroidsReset(int param1, int param2, void* extra) {
    // TODO: modify number of asteroids based on score
    spawnAsteroids(4);
}