#ifndef SCREEN_H
#define SCREEN_H


#include "engine/util/CommonIncludes.h"
#include <map>
#include <QGLWidget>
#include <QTime>
#include <QTimer>
#include <memory>
#include <engine/graphics/Graphics.h>
#include <engine/graphics/Camera.h>


class screen
{
public:
    screen();
    virtual ~screen();



    void ticker(float seconds) { tick(seconds); }
    void drawer(Graphics* g)  { draw(g); }
    void onKeyPresseder(QKeyEvent*event)  { onKeyPressed(event); }
    void onMouseDraggeder(QMouseEvent*event, int dx, int dy) { onMouseDragged(event, dx, dy); }
    void setuper(Graphics* g) { setup(g);  }
    void resizeer(Graphics* g, int w, int h) { resize(g, w, h); }
    void keyRepeatEventer(QKeyEvent *event) { keyRepeatEvent(event);  }
    void keyReleaseEventer(QKeyEvent *event) { keyReleaseEvent(event); }
    void releaseKeyser() { releaseKeys(); }
    virtual std::shared_ptr<Camera> getcamer() { return getcam(); }

private:


    virtual void tick(float seconds);
    virtual void draw(Graphics* g);
    virtual void onKeyPressed(QKeyEvent*event);
    // more device and event types here...
    virtual void onMouseDragged(QMouseEvent*event, int dx, int dy);
    virtual void setup(Graphics* g);
    virtual void resize(Graphics* g, int w, int h);
    virtual void keyRepeatEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void releaseKeys();
    virtual std::shared_ptr<Camera> getcam();

    std::shared_ptr<Camera> m_camera;

};

#endif // SCREEN_H
