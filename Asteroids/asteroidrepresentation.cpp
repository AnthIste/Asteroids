#include "asteroidrepresentation.h"
#include "asteroid.h"
#include <time.h>

AsteroidRepresentation::AsteroidRepresentation() {
}

AsteroidRepresentation::~AsteroidRepresentation() {
}

void AsteroidRepresentation::render(LPDIRECT3DDEVICE9 d3ddev) {
    Asteroid* asteroid = dynamic_cast<Asteroid*>(getEntity());

    int entityX = (int)getEntity()->getX();
    int entityY = (int)getEntity()->getY();

    // Render the asteroid
    int sizeFactor = asteroid->getSize() * 10;

    srand(asteroid->getId());
    int r = rand()%200;
    int g = rand()%200;
    int b = rand()%200;
    
    D3DRECT rect = {entityX-sizeFactor, entityY-sizeFactor, entityX+sizeFactor, entityY+sizeFactor};
    d3ddev->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(r, g, b), 1.0f, 0);

    D3DRECT rect2 = {entityX-4, entityY-4, entityX+4, entityY+4};
    d3ddev->Clear(1, &rect2, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0);
}