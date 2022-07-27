#include "DrawSystem.h"

DrawSystem::DrawSystem()
{

}

void DrawSystem::drawObjs(Graphics* g)
{

    for (auto& x : m_objects)
    {
        GameObject obj = x.second;
        if(obj.isComponent("DrawableComponent"))
        {

            if(obj.portal_forward != glm::vec3())
            {
                //g->setPortal(1);
                float i = 1.f;
                glVertexAttrib4fv(10, &i);
            }
            else
            {
                //g->setPortal(0);
                float i = 0.f;
                glVertexAttrib4fv(10, &i);
            }

            (x.second.getComponent("DrawableComponent"))->onDrawer(g);
        }
    }
}

void DrawSystem::addObj(std::string name, GameObject gameObj)
{
    m_objects[name] = gameObj;

}

void DrawSystem::remObj(std::string name)
{
    m_objects.erase(name);

}
