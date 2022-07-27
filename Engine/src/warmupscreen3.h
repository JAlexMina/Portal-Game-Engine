#ifndef WARMUPSCREEN3_H
#define WARMUPSCREEN3_H

#include "engine/util/CommonIncludes.h"
#include <map>
#include <QGLWidget>
#include <QTime>
#include <QTimer>
#include <memory>
#include <engine/graphics/Graphics.h>
#include <engine/graphics/Camera.h>
#include <QApplication>
#include <QKeyEvent>
#include "screen.h"


class warmupscreen3 : public screen
{
public:
    warmupscreen3();

    void tick(float seconds);
    void draw(Graphics* g);
    void onKeyPressed(QKeyEvent*event);
    // more device and event types here...
    void onMouseDragged(QMouseEvent*event, int dx, int dy);
    void setup(Graphics* g);
    void resize(Graphics* g, int w, int h);
    void keyRepeatEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void releaseKeys();
    std::shared_ptr<Camera> getCam();
    int doub;

    double m_accelerationG;
    double m_velocity;
    glm::vec3 m_look;
    glm::vec3 m_dir;
    glm::vec3 m_perp;
    float m_dx;
    float m_dy;
    glm::vec3 pos;
    float m_camDistance;
    float mx;
    float sec;

    Graphics* m_g;



    std::map<std::string, bool> keys;

    std::shared_ptr<Camera> m_camera;
};

#endif // WARMUPSCREEN3_H
