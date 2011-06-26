#include "spaceshiprepresentation.h"
#include "spaceship.h"

SpaceshipRepresentation::SpaceshipRepresentation() {
}

SpaceshipRepresentation::~SpaceshipRepresentation() {
}

void SpaceshipRepresentation::render(LPDIRECT3DDEVICE9 d3ddev) {
    Spaceship* spaceship = dynamic_cast<Spaceship*>(getEntity());

    int entityX = (int)getEntity()->getX();
    int entityY = (int)getEntity()->getY();

    D3DRECT rect = {entityX-25, entityY-25, entityX + 25, entityY + 25};
    d3ddev->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(150, 140, 100), 1.0f, 0);

    double rotation = spaceship->getRotationRadians();

    int rotationX = static_cast<int>(entityX + 25.0 * cos(rotation));
    int rotationY = static_cast<int>(entityY + 25.0 * sin(rotation));

    D3DRECT rect2 = {rotationX-5, rotationY-5, rotationX + 5, rotationY + 5};
    d3ddev->Clear(1, &rect2, D3DCLEAR_TARGET, D3DCOLOR_XRGB(190, 60, 100), 1.0f, 0);

    double rotationTarget = spaceship->getRotationTargetRadians();

    int targetX = static_cast<int>(entityX + 25.0 * cos(rotationTarget));
    int targetY = static_cast<int>(entityY + 25.0 * sin(rotationTarget));

    D3DRECT rect3 = {targetX-2, targetY-2, targetX + 2, targetY + 2};
    d3ddev->Clear(1, &rect3, D3DCLEAR_TARGET, D3DCOLOR_XRGB(290, 0, 100), 1.0f, 0);

    double rotationVelocity = spaceship->getVelocity().getDirectionRadians();

    int velocityX = static_cast<int>(entityX + 40.0 * cos(rotationVelocity));
    int velocityY = static_cast<int>(entityY + 40.0 * sin(rotationVelocity));

    D3DRECT rect4 = {velocityX-2, velocityY-2, velocityX + 2, velocityY + 2};
    d3ddev->Clear(1, &rect4, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
}