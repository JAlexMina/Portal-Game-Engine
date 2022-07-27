#ifndef ENEMYRESPONSECOMPONENT_H
#define ENEMYRESPONSECOMPONENT_H

#include "Component.h"


class EnemyResponseComponent : public Component
{
public:
    EnemyResponseComponent(glm::vec3 pos);

    glm::vec3 onTick(glm::vec3 pos1, glm::vec3 pos2);
    void print(glm::vec3 pos1, glm::vec3 pos2, glm::vec3* pos3);


    glm::vec3 m_position;
};

#endif // ENEMYRESPONSECOMPONENT_H
