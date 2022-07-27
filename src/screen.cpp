#include "screen.h"

screen::screen()
{

}

screen::~screen()
{

}


void screen::tick(float seconds){}
void screen::draw(Graphics* g){}
void screen::onKeyPressed(QKeyEvent*event){}

void screen::onMouseDragged(QMouseEvent*event, int dx, int dy){}
void screen::setup(Graphics* g){}
void screen::resize(Graphics* g, int w, int h){}
void screen::keyRepeatEvent(QKeyEvent *event){}
void screen::keyReleaseEvent(QKeyEvent *event){}
void screen::releaseKeys(){}
std::shared_ptr<Camera> screen::getcam(){}

