#include "starfield.h"
#include <cstdlib>
#include <time.h>

Starfield::Starfield(int cellWidth, int cellHeight) {
    srand(time(0));

    pRoot = new Cell(rand()%666);
    pRoot->pDown = new Cell(rand()%666);
    pRoot->pRight = new Cell(rand()%666);
    pRoot->pRight->pDown = new Cell(rand()%666);
    pRoot->pDown->pRight = pRoot->pRight->pDown;

    pRoot->pRight->pRight = 0;
    pRoot->pDown->pDown = 0;
    pRoot->pRight->pDown->pRight = 0;
    pRoot->pRight->pDown->pDown = 0;

    this->cellWidth = cellWidth;
    this->cellHeight = cellHeight;

    scrollX = 0.0;
    scrollY = 0.0;
}

Starfield::~Starfield() {
    delete pRoot->pRight->pDown;
    delete pRoot->pRight;
    delete pRoot->pDown;
    delete pRoot;
}

void Starfield::scroll(double dx, double dy) {
    scrollX += dx;
    scrollY += dy;

    if (scrollX < 0) {
        scrollX += cellWidth;
        overflowHorizontal();
    } else if (scrollX > cellWidth) {
        scrollX -= cellWidth;
        overflowHorizontal();
    }

    if (scrollY < 0) {
        scrollY += cellHeight;
        overflowVertical();
    } else if (scrollY > cellHeight) {
        scrollY -= cellHeight;
        overflowVertical();
    }
}

void Starfield::render(LPDIRECT3DDEVICE9 d3ddev) {
    unmarkCells(pRoot);
    renderCell(d3ddev, pRoot, 0, 0);
}

void Starfield::renderCell(LPDIRECT3DDEVICE9 d3ddev, Starfield::Cell* cell, int xOffset, int yOffset) {
    if (cell == 0 || cell->bRendered == true) return;

    srand(cell->seed);

    for (int k = 0; k < 100; k++) {
        int x = rand() % cellWidth - static_cast<int>(scrollX) + xOffset;
        int y = rand() % cellHeight - static_cast<int>(scrollY) + yOffset;

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

    cell->bRendered = true;
    renderCell(d3ddev, cell->pRight, xOffset + cellWidth, yOffset);
    renderCell(d3ddev, cell->pDown, xOffset, yOffset + cellHeight);
}

void Starfield::unmarkCells(Cell* pCell) {
    if (pCell == 0 || pCell->bRendered == false) return;

    pCell->bRendered = false;
    unmarkCells(pCell->pRight);
    unmarkCells(pCell->pDown);
}

void Starfield::overflowVertical() {
    Cell* pTmp = pRoot;
    pRoot = pRoot->pDown;
    pRoot->pDown = pTmp;
    pRoot->pDown->pDown = 0;

    pRoot->pRight->pDown = pRoot->pDown->pRight;
    pRoot->pDown->pRight->pDown = 0;
}

void Starfield::overflowHorizontal() {
    Cell* pTmp = pRoot;
    pRoot = pRoot->pRight;
    pRoot->pRight = pTmp;
    pRoot->pRight->pRight = 0;

    pRoot->pDown->pRight = pRoot->pRight->pDown;
    pRoot->pRight->pDown->pRight = 0;
}