#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <map>
#include "GameObject.h"


class systems
{
public:
    systems();

    void onTick(float seconds);

protected:
    std::map<std::string, GameObject> m_objects;
};

#endif // SYSTEMS_H
