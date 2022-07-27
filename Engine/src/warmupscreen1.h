#ifndef WARMUPSCREEN1_H
#define WARMUPSCREEN1_H


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


class warmupScreen1 : public screen
{
public:
    warmupScreen1();


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

    std::shared_ptr<Camera> getcam();


    double m_accelerationG;
    double m_velocity;
    glm::vec3 m_look;
    glm::vec3 m_dir;
    glm::vec3 m_perp;
    float m_sec = 0;


    std::map<std::string, bool> keys;

    std::shared_ptr<Camera> m_camera;
};

#endif // WARMUPSCREEN1_H
