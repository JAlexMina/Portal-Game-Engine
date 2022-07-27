#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>
#include "Component.h"
#include "Room.h"


class GameObject
{
public:
    GameObject();
    //GameObject(std::shared_ptr<Camera> camera);

    void addComponent(Component* compo, std::string string);
    void removeComponent(std::string string);
    void onTick(float seconds);
    Component* getComponent(std::string name);
    bool isComponent(std::string string);
    void print();
    std::map<std::string, Component*> get_components();
    glm::vec3 m_position;
    float m_velocity;
    float sec;
    std::string name;
    bool goen = false;
    std::map<std::string, Component*> m_components;
    Room r;
    Room rl;
    glm::vec3 oldp = glm::vec3();

    glm::vec3 portal_forward = glm::vec3();
    glm::vec3 portal_up = glm::vec3();
    glm::vec3 portal_right = glm::vec3();

    glm::vec3 currC_Pos = glm::vec3();

private:

};

#endif // GAMEOBJECT_H
