#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include "systems.h"
#include "drawablecomponent.h"
#include "engine/graphics/Graphics.h"


class DrawSystem : public systems
{
public:
    DrawSystem();
    void drawObjs(Graphics* g);
    void addObj(std::string name, GameObject gameObj);
    void remObj(std::string name);
};

#endif // DRAWSYSTEM_H
