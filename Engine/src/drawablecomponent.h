#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include "Component.h"
#include "engine/graphics/Graphics.h"
#include "engine/util/CommonIncludes.h"
#include "TransformComponent.h"
#include "engine/graphics/Shape.h"
#include "engine/graphics/FBO.h"
#include "engine/graphics/Texture2D.h"

class DrawableComponent : public Component
{
public:
    DrawableComponent(std::string loc, std::string name, std::string shape, bool port, glm::vec2 repeat = glm::vec2(1.f, 1.f));
//    DrawableComponent(std::string loc, std::string name, Shape* s, Graphics* g, glm::vec2 repeat = glm::vec2(1.f, 1.f));
    DrawableComponent(std::string loc, std::string name, glm::vec2 repeat = glm::vec2(1.f, 1.f));
    virtual void onDraw(Graphics* g);
    Material m_material;
    std::string m_shape = "";
    Shape* m_s;
    std::string m_name;
    std::string m_loc;
    glm::vec2 m_repeat;
    void addMaterial(Graphics* g);

    FBO* m_blurFBO;

    void addMaterialPortal(FBO* FBO);
    bool portal;

    TransformComponent* transform;
};

#endif // DRAWABLECOMPONENT_H
