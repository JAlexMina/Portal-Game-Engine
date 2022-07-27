#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Component.h"
#include "engine/graphics/Graphics.h"
#include "engine/util/CommonIncludes.h"


class TransformComponent : public Component
{
public:
    TransformComponent(glm::vec3 loc, float size);
    TransformComponent(glm::vec3 loc, float xSize, float ySize, float zSize);

    void transform(Graphics* g);
    void setRotate(glm::vec3 rot1, float the1, glm::vec3 rot2, float the2);

    glm::vec3 m_loc;
    float m_size = 1;
    float x, y , z = 1;
    glm::vec3 rotate1 = glm::vec3(0.f, 0.f, 1.f);
    float theta1 = 0;

    glm::vec3 rotate2 = glm::vec3(0.f, 0.f, 1.f);
    float theta2 = 0;

    bool mash = false;
};

#endif // TRANSFORMCOMPONENT_H
