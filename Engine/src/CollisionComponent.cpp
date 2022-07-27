#include "CollisionComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

//Class that holds the collision cylinder

CollisionComponent::CollisionComponent(glm::vec3 pos, float rad, float h, std::string t, bool nonMoveable, std::shared_ptr<Camera> camera) :
    m_type(t),
    circlePos(pos),    
    circleRad(rad),
    height(h),        
    vertVelocity(0),
    m_nonMoveable(nonMoveable),
    m_camera(camera)
{

}

CollisionComponent::CollisionComponent(glm::vec3 pos, float width, float height, float length, std::string t, bool nonMoveable, std::shared_ptr<Camera> camera) :
    m_type(t),
    quadPos(pos),
    w(width),
    h(height),
    length(length),
    vertVelocity(0),
    m_nonMoveable(nonMoveable),
    m_camera(camera)
{

}



CollisionComponent::CollisionComponent(glm::vec3 pos, float width, float height, float length, std::string t, bool nonMoveable, std::shared_ptr<Camera> camera, std::string port) :
    m_type(t),
    portal(port),
    quadPos(pos),
    w(width),
    h(height),
    length(length),
    vertVelocity(0),
    m_nonMoveable(nonMoveable),
    m_camera(camera)
{

}



CollisionComponent::CollisionComponent(int numWalls, std::vector<cube> walls, std::shared_ptr<Camera> camera, bool waa):
    m_type("cube"),
    m_numWalls(numWalls),
    m_walls(walls),
    wa(waa),
    m_camera(camera)
{

}

void CollisionComponent::fp(glm::vec3 pos)
{
    circlePos = pos;
}

void CollisionComponent::changeCubePosition(glm::vec3 pos)
{
    quadPos = pos;
}

void CollisionComponent::transformC(float x, float z)
{


        for(size_t i = 0; i < m_walls.size(); i++)
        {
            m_walls[i].p1.x += x;
            m_walls[i].p1.z += z;

            m_walls[i].p2.x += x;
            m_walls[i].p2.z += z;

        }

}
