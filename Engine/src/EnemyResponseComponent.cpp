#include "EnemyResponseComponent.h"

EnemyResponseComponent::EnemyResponseComponent(glm::vec3 pos) :
    m_position(pos)
{

}

void EnemyResponseComponent::print(glm::vec3 pos1, glm::vec3 pos2, glm::vec3* pos3)
{
    glm::vec3 dir = glm::normalize(glm::vec3((pos2 - pos1).x, 0, (pos2 - pos1).z));
    float speed = 0.07f;
    (*pos3) = (*pos3) + (speed*-dir);
}


glm::vec3 EnemyResponseComponent::onTick(glm::vec3 pos1, glm::vec3 pos2)
{
//    m_position = pos2;
//    glm::vec3 to = m_position - pos1;
//    float speed = 0.1f;
//    m_position += speed*to;
    return m_position;


}
