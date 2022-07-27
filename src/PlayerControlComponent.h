#ifndef PLAYERCONTROLCOMPONENT_H
#define PLAYERCONTROLCOMPONENT_H

#include "Component.h"
#include <QKeyEvent>


class PlayerControlComponent : public Component
{
public:
    PlayerControlComponent();

    std::map<std::string, bool> keys;

    void onKeyPress(QKeyEvent*event);
    void onKeyRelease(QKeyEvent*event);
    void onTick(std::shared_ptr<Camera> camera, bool*isThirdPerson);
    void onMouseDragged(QMouseEvent*event, int dx, int dy);
    void releaseKeys();
    void moveBack(glm::vec3 m);


    float m_dx;
    float m_dy;
    float mx;

    glm::vec3 pos;
    glm::vec3 m_look;
    glm::vec3 m_dir;
    glm::vec3 m_perp;
    float cam_velocity;
    std::shared_ptr<Camera> m_camera;
    bool* itp;
    bool wall = false;
};

#endif // PLAYERCONTROLCOMPONENT_H
