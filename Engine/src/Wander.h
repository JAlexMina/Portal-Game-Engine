#ifndef WANDER_H
#define WANDER_H

#include "BehaviorTreeNode.h"
#include "Room.h"
#include "GameObject.h"


class Wander : BehaviorTreeNode
{
public:
    Wander();

    const static int sizeOfChunk = 9;
    const static int sizeOfRoom = 10;
    Room rooms[sizeOfChunk][sizeOfChunk];


    void setRooms(Room r[sizeOfChunk][sizeOfChunk]);
    Room wander(Room curr, int last, int seed);
    void going(GameObject* obj, Room goTo, glm::vec3 startingPos);

    std::string wanderingAction(GameObject* strOBJ, glm::vec3* startPos);

    Status update(float seconds);
    void reset();






private:
    int sede = 739;
    bool wandering = true;
};

#endif // WANDER_H
