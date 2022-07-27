#include "drawablecomponent.h"
#include "GameObject.h"


DrawableComponent::DrawableComponent(std::string loc, std::string name, std::string shape, bool port, glm::vec2 repeat) :
    m_shape(shape),    
    m_name(name),
    m_loc(loc),
    m_repeat(repeat),
    portal(port)
{
    m_material.portal = port;
}

//Chunks
DrawableComponent::DrawableComponent(std::string loc, std::string name, glm::vec2 repeat) :
    m_shape("Chunk"),    
    m_name(name),
    m_loc(loc),
    m_repeat(repeat)
{

}






void DrawableComponent::addMaterial(Graphics* g)
{
    g->addTexture(m_name, m_loc);
    m_material.textureName = m_name;
    g->addMaterial(m_name, m_material);
}


void DrawableComponent::addMaterialPortal(FBO* FBO)
{
    m_blurFBO = FBO;
}

void DrawableComponent::onDraw(Graphics* g)
{
    g->setMaterial(m_name);
    g->clearTransform();
    g->scale(1);



    if(portal)
    {
        m_blurFBO->getColorAttachment(0).bind();
    }
    else
    {
        g->setMaterial(m_name);
    }

    g->translate(transform->m_loc);
    g->rotate(transform->theta1, transform->rotate1);
    g->rotate(transform->theta2, transform->rotate2);


    if(transform->mash)
    {
        g->scale(transform->m_size);
    }
    else
    {
        g->scale(glm::vec3(transform->x, transform->y, transform->z));
    }

    g->setTextureRepeat(m_repeat);
    g->drawShape(m_shape);
}
