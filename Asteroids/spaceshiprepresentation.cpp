#include "spaceshiprepresentation.h"
#include "spaceship.h"

SpaceshipRepresentation::SpaceshipRepresentation() {
}

SpaceshipRepresentation::~SpaceshipRepresentation() {
}

void SpaceshipRepresentation::render(LPDIRECT3DDEVICE9 d3ddev) {
    Spaceship* spaceship = dynamic_cast<Spaceship*>(getEntity());
    double velocityMagnitude = spaceship->getVelocity().getMagnitude();

    int entityX = (int)getEntity()->getX();
    int entityY = (int)getEntity()->getY();

    // Render the spaceship
    double rotation = spaceship->getRotationRadians();
    int spaceshipLength = static_cast<int>(spaceship->getHitRadius());
    int numPasses = 7;
    int initialSize = spaceshipLength*3/numPasses;

    for (int k = 0; k <= numPasses; k++) {
        int rotationX = static_cast<int>(entityX + k*numPasses * cos(rotation));
        int rotationY = static_cast<int>(entityY + k*numPasses * sin(rotation));

        D3DRECT rect2 = {rotationX-(initialSize-k+1), rotationY-(initialSize-k+1), rotationX + (initialSize-k+1), rotationY + (initialSize-k+1)};
        d3ddev->Clear(1, &rect2, D3DCLEAR_TARGET, D3DCOLOR_XRGB(170, 140, 100), 1.0f, 0);
    }

    // Render a flame trail
    for (int k = 0; k <= (int)velocityMagnitude*2; k++) {
        int rotationX = static_cast<int>(entityX - (k*(int)velocityMagnitude + 10) * cos(rotation));
        int rotationY = static_cast<int>(entityY - (k*(int)velocityMagnitude + 10) * sin(rotation));

        D3DRECT rect2 = {rotationX-((int)velocityMagnitude-k), rotationY-((int)velocityMagnitude-k), rotationX + ((int)velocityMagnitude-k), rotationY + ((int)velocityMagnitude-k)};
        d3ddev->Clear(1, &rect2, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 238, 0), 1.0f, 0);
    }

    // Render the rotation target that the ship is aiming for
    double rotationTarget = spaceship->getRotationTargetRadians();

    int targetX = static_cast<int>(entityX + 25.0 * cos(rotationTarget));
    int targetY = static_cast<int>(entityY + 25.0 * sin(rotationTarget));

    D3DRECT rect3 = {targetX-2, targetY-2, targetX + 2, targetY + 2};
    d3ddev->Clear(1, &rect3, D3DCLEAR_TARGET, D3DCOLOR_XRGB(290, 0, 100), 1.0f, 0);

    // Render the direction/magnitude of the current ship velocity
    double rotationVelocity = spaceship->getVelocity().getDirectionRadians();

    int velocityX = static_cast<int>(entityX + 40.0 * cos(rotationVelocity) * spaceship->getVelocity().getMagnitude() * 0.5);
    int velocityY = static_cast<int>(entityY + 40.0 * sin(rotationVelocity) * spaceship->getVelocity().getMagnitude() * 0.5);

    D3DRECT rect4 = {velocityX-2, velocityY-2, velocityX + 2, velocityY + 2};
    d3ddev->Clear(1, &rect4, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
}