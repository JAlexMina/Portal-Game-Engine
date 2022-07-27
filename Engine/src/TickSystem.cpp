#include "TickSystem.h"


TickSystem::TickSystem()
{

}

void TickSystem::tickObjs(float seconds)
{
    for (auto& x : m_objects)
    {
        x.second.onTick(seconds);
    }
}
