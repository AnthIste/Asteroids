#include "spaceshiprepresentation.h"

SpaceshipRepresentation::SpaceshipRepresentation() {
}

SpaceshipRepresentation::~SpaceshipRepresentation() {
}

void SpaceshipRepresentation::render(LPDIRECT3DDEVICE9 d3ddev) {
    D3DRECT rect = {(int)getEntity()->getX(), (int)getEntity()->getY(), (int)getEntity()->getX() + 50, (int)getEntity()->getY() + 50};
    d3ddev->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(150, 140, 100), 1.0f, 0);
}