#ifndef APPLICATION_H
#define APPLICATION_H

#include "engine/util/CommonIncludes.h"
#include <map>
#include <QGLWidget>
#include <QTime>
#include <QTimer>
#include <memory>
#include <engine/graphics/Graphics.h>
#include <engine/graphics/Camera.h>
#include "screen.h"
#include "warmupscreen1.h"
#include "warmupscreen2.h"
//#include "warmupscreen3.h"
#include "GameWorld.h"


class Application
{
public:
    Application();

    public:
        void tick(float seconds);
        void draw(Graphics* g);
        void onKeyPressed(QKeyEvent*event);
        // more device and event types here...
        void onMouseDragged(QMouseEvent*event, int dx, int dy);
        void setup(Graphics* g, bool* mt);
        void resize(Graphics* g, int w, int h);
        void keyRepeatEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);

        bool* m_mt;


        warmupScreen1 screen1;
        warmupscreen2 screen2;
        //warmupscreen3 screen3;
        GameWorld m_gameworld;
        int once = 0;

        screen* activeScreen;
        screen* nextActive;
        screen* nextnextActive;
        Graphics* m_g;

};

#endif // APPLICATION_H
