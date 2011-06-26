#include "bulletrepresentation.h"
#include "bullet.h"

BulletRepresentation::BulletRepresentation() {
}

BulletRepresentation::~BulletRepresentation() {
}

void BulletRepresentation::render(LPDIRECT3DDEVICE9 d3ddev) {
    Bullet* bullet = dynamic_cast<Bullet*>(getEntity());

    int entityX = (int)getEntity()->getX();
    int entityY = (int)getEntity()->getY();

    // Render the bullet
    
    D3DRECT rect = {entityX-2, entityY-2, entityX+2, entityY+2};
    d3ddev->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
}