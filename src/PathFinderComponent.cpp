#include "PathFinderComponent.h"

PathFinderComponent::PathFinderComponent(bool searching, glm::vec3 d) :
    is_searching(searching),
    destination(d)
{

}

void PathFinderComponent::changeDestination(glm::vec3 pos)
{
    destination = pos;
}

void PathFinderComponent::change_is_searching(bool s)
{
    is_searching = s;
}
