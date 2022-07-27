#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "systems.h"
#include "CollisionComponent.h"


class CollisionSystem : public systems
{
public:
    CollisionSystem();
    void onTick(bool* lose);
    void onTickWalls(GameObject obj1, GameObject obj2);
    void addObj(std::string name, GameObject gameObj);
    void remObj(std::string name);
    glm::vec3 checkCollisionWallCylinder(cube c, Component* cylinder);
    GameObject* portals[2] = {NULL, NULL};
};

#endif // COLLISIONSYSTEM_H
