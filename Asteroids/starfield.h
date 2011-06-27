#ifndef ASTEROIDS_STARFIELD_H_
#define ASTEROIDS_STARFIELD_H_

#include <d3d9.h>

class Starfield {
struct Cell {
    Cell(int seed) { this->seed = seed; bRendered = false; }
    bool bRendered;
    int seed;
    Cell* pRight;
    Cell* pDown;
};

public:
    Starfield(int cellWidth, int cellHeight);
    virtual ~Starfield();

    void scroll(double dx, double dy);
    virtual void render(LPDIRECT3DDEVICE9 d3ddev);
    void renderCell(LPDIRECT3DDEVICE9 d3ddev, Starfield::Cell* cell, int x, int y);
    void unmarkCells(Cell* pCell);

private:
    void overflowVertical();
    void overflowHorizontal();

private:
    double scrollX;
    double scrollY;
    int cellWidth;
    int cellHeight;

    Cell* pRoot;

};

#endif  // ASTEROIDS_STARFIELD_H_