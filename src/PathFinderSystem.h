#ifndef PATHFINDERSYSTEM_H
#define PATHFINDERSYSTEM_H

#include "systems.h"
#include "Room.h"

class PathFinderSystem : systems
{
public:
    PathFinderSystem();

     const static int sizeOfChunk = 9;
     const static int sizeOfRoom = 10;



    void onTick(int seconds, float offset, glm::vec3 n, glm::vec3 e, glm::vec3 s, glm::vec3 w);
    void addObj(std::string name, GameObject gameObj);
    void setRooms(Room r[sizeOfChunk][sizeOfChunk]);
    Room wander(Room curr, int last, int seed);
    void going(GameObject* obj, Room goTo, glm::vec3 startingPos);

    std::string wanderingAction(GameObject* strOBJ, glm::vec3* startPos);






    Room rooms[sizeOfChunk][sizeOfChunk];

private:
    int sede = 739;
    bool wandering = true;

};

#endif // PATHFINDERSYSTEM_H
