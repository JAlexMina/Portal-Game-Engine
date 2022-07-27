#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include "systems.h"


class TickSystem : public systems
{
public:
    TickSystem();
    void tickObjs(float seconds);
};

#endif // TICKSYSTEM_H
