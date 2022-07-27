#ifndef PATHFINDERCOMPONENT_H
#define PATHFINDERCOMPONENT_H

#include "Component.h"

class PathFinderComponent : public Component
{
public:

    PathFinderComponent(bool searching, glm::vec3 d);

    void changeDestination(glm::vec3 pos);
    void change_is_searching(bool s);



    bool is_searching;
    glm::vec3 destination;

};

#endif // PATHFINDERCOMPONENT_H
