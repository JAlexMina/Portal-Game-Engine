#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"
#include "engine/graphics/Camera.h"


struct cube{

  glm::vec3 pos;
  float height;
  float width;
  float x;
  float z;

  glm::vec3 p1;
  glm::vec3 p2;

  bool operator == (const cube &p)
  {
     if( p1 == p.p1 && p2 == p.p2 )
       return true;
     else
       return false;
  }

};




class CollisionComponent : public Component
{
public:
    CollisionComponent(glm::vec3 pos, float rad, float h, std::string t, bool nonMoveable, std::shared_ptr<Camera> camera);
    CollisionComponent(glm::vec3 pos, float width, float height, float length, std::string t, bool nonMoveable, std::shared_ptr<Camera> camera);
    CollisionComponent(glm::vec3 pos, float width, float height, float length, std::string t, bool nonMoveable, std::shared_ptr<Camera> camera, std::string port);
    CollisionComponent(int numWalls, std::vector<cube> walls, std::shared_ptr<Camera> camera, bool waa);


    std::string m_type = "cube";

    std::string portal = "";
    //cylinder
    glm::vec3 circlePos; //middle
    float circleRad;
    float height;

    //cube
    glm::vec3 quadPos;
    float w;
    float h;
    float length;

    //walls
    int m_numWalls = -1;
    std::vector<cube> m_walls;
    bool wa = false;

    float vertVelocity;

    void fp(glm::vec3 pos);

    void changeCubePosition(glm::vec3 pos);
    void transformC(float x, float z);

    bool m_nonMoveable = false;
    std::shared_ptr<Camera> m_camera;
};

#endif // COLLISIONCOMPONENT_H
