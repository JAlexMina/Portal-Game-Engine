#ifndef CHUNK_H
#define CHUNK_H

#include "Room.h"
#include "GameObject.h"
#include "CollisionComponent.h"


enum Directions { NORTH = 0, SOUTH = 1, EAST = 2, WEST = 3 };


class Chunk : public GameObject
{
public:
    Chunk();
    void makeChunk(int x, int y, int seed);
    void printChunk();
    bool isMiddle(int x);
    std::shared_ptr<Shape> makeShape(bool floor);
    std::vector<cube> m_walls;
    int nW = 0;
    const static int sizeOfChunk = 1;
    Room rooms[sizeOfChunk][sizeOfChunk];


private:
    bool isInBounds(int x, int y);





    float dim = 25;
    float ydim = 15;
};

#endif // CHUNK_H
