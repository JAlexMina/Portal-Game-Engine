#include "GameObject.h"
#include "engine/graphics/Camera.h"

//GameObject::GameObject(std::shared_ptr<Camera> camera) :
//    m_camera(camera)
//{

//}

GameObject::GameObject() :
    m_velocity(0)
{

}


void GameObject::addComponent(Component* compo, std::string string)
{
    m_components[string] = compo;
}

void GameObject::removeComponent(std::string string)
{
    m_components.erase(string);
}

Component* GameObject::getComponent(std::string name)
{
    return m_components[name];
}

bool GameObject::isComponent(std::string string)
{

    bool b = ((m_components.count(string)) > 0);
    return b;
}

void GameObject::onTick(float seconds)
{
    sec +=seconds;
}

void GameObject::print()
{
    std::cout << "print" << std::endl;
}

std::map<std::string, Component*> GameObject::get_components()
{
    return m_components;
}
