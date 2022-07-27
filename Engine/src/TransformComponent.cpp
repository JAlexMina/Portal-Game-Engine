#include "TransformComponent.h"

TransformComponent::TransformComponent(glm::vec3 loc, float size) :
    m_size(size),
    m_loc(loc)
{
    mash = true;
}

TransformComponent::TransformComponent(glm::vec3 loc, float xSize, float ySize, float zSize) :
    m_loc(loc),
    x(xSize),
    y(ySize),
    z(zSize)
{
    mash = false;
}

void TransformComponent::transform(Graphics* g)
{
    g->translate(m_loc);
    g->scale(m_size);
}

void TransformComponent::setRotate(glm::vec3 rot1, float the1, glm::vec3 rot2, float the2)
{
    rotate1 = rot1;
    theta1 = the1;
    rotate2 = rot2;
    theta2 = the2;
}
