#include "application.h"
#include <QApplication>
#include <QKeyEvent>
#include <QGLWidget>

Application::Application()
{
    activeScreen = &m_gameworld;
    nextActive = &screen2;
    //activeScreen = &screen1;
}

void Application::setup(Graphics* g, bool* mt)

{

    m_mt = mt;
    screen2.setup(g);
    screen1.setup(g);
    m_gameworld.setup(g);    
    g->setCamera(m_gameworld.m_camera);
    m_g = g;

}

void Application::resize(Graphics* g, int w, int h)
{ 
    activeScreen->resizeer(g, w, h);
}


void Application::tick(float seconds)
{

    activeScreen->ticker(seconds);

}

void Application::draw(Graphics* g)
{    
    activeScreen->drawer(g);

}

void Application::onKeyPressed(QKeyEvent*event)
{

    if (event->key() == Qt::Key_Escape) QApplication::quit();

    if(event->key() == Qt::Key_P )
    {
        //might do somehting different here to
        //like holding all the screens in a list
        //but since there are only 2 swapping is fine

        activeScreen->releaseKeyser();
        screen* swap = activeScreen;
        activeScreen = nextActive;
        nextActive = swap;
        if(activeScreen == &screen2)
        {
            QApplication::setOverrideCursor(Qt::ArrowCursor);
            (*m_mt) = (false);
        }
        else
        {
            QApplication::setOverrideCursor(Qt::BlankCursor);
            (*m_mt) = (true);
        }
        m_g->setCamera(activeScreen->getcamer());
    }

    activeScreen->onKeyPresseder(event);
}

void Application::onMouseDragged(QMouseEvent* event, int dx, int dy)
{
    activeScreen->onMouseDraggeder(event, dx, dy);
}

void Application::keyRepeatEvent(QKeyEvent *event)
{
    activeScreen->keyRepeatEventer(event);
}

void Application::keyReleaseEvent(QKeyEvent *event)
{
    activeScreen->keyReleaseEventer(event);
}
