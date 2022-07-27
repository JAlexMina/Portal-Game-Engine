#include "CollisionSystem.h"
#include <math.h>
#include "TransformComponent.h"
#include "drawablecomponent.h"
#include "EnemyResponseComponent.h"
#include "PlayerControlComponent.h"
#include "engine/graphics/Camera.h"

CollisionSystem::CollisionSystem()
{

}


glm::vec3 checkCollisionCylinderCylinder(Component* cc1, Component* cc2)
{


    float radius1 = ((CollisionComponent*)cc1)->circleRad;
    float radius2 = ((CollisionComponent*)cc2)->circleRad;

    glm::vec3 pos1 = ((CollisionComponent*)cc1)->circlePos;
    glm::vec3 pos2 = ((CollisionComponent*)cc2)->circlePos;

    float height1 = ((CollisionComponent*)cc1)->height;
    float height2 = ((CollisionComponent*)cc2)->height;

    float dist = glm::sqrt((pow(pos2.x - pos1.x, 2.f)) + (pow(pos2.z - pos1.z, 2.f)));

    if(dist < radius1+radius2)
    {
        if(glm::abs(pos1.y - pos2.y) < (0.5f*height1) + (0.5f*height2))
        {
            return (1.f*(radius1+radius2 -dist))*glm::vec3(pos2.x-pos1.x, 0 , pos2.z-pos1.z);
        }

    }

    return glm::vec3(-1, -1, -1);
}




glm::vec3 checkCollisionCubeCylinder(Component* cube, Component* cylinder)
{
    float cylRadius = ((CollisionComponent*)cylinder)->circleRad;

    float w = ((CollisionComponent*)cube)->w;
    float h = ((CollisionComponent*)cube)->h;
    float l = ((CollisionComponent*)cube)->length;


    glm::vec3 CubePos = ((CollisionComponent*)cube)->quadPos;
    glm::vec3 CylinderPos = ((CollisionComponent*)cylinder)->circlePos;

    float cylinderHeight = ((CollisionComponent*)cylinder)->height;


    glm::vec3 closesteP = glm::vec3(glm::clamp(CylinderPos.x, CubePos.x - (w/2), CubePos.x + (w/2)), CylinderPos.y, glm::clamp(CylinderPos.z, CubePos.z - (l/2), CubePos.z + (l/2)));



    if(glm::pow(glm::length(closesteP-CylinderPos), 2) <= glm::pow(cylRadius, 2))
    {
        if(glm::abs(CubePos.y - CylinderPos.y) < (0.5f*cylinderHeight) + (0.5f*h))
        {            
            glm::vec3 p2 = (closesteP - CylinderPos);
            if(p2.x == 0.f && p2.y == 0.f && p2.z == 0.f)
            {
                p2.x = 0.1f;
                p2.y = 0.0f;
                p2.z = 0.1f;
            }

            return (1-glm::length(closesteP-CylinderPos)) * glm::normalize(p2);
        }

    }


    return glm::vec3(-1, -1, -1);
}

glm::vec3 CollisionSystem::checkCollisionWallCylinder(cube c, Component* cylinder)
{


    float cylRadius = ((CollisionComponent*)cylinder)->circleRad;

    glm::vec3 p1 = c.p1;
    glm::vec3 p2 = c.p2;

    p1.y = 0;
    p2.y = 0;

    glm::vec3 CylinderPos = ((CollisionComponent*)cylinder)->circlePos;

    CylinderPos.y = 0;



    glm::vec3 closesteP = glm::vec3(glm::clamp(CylinderPos.x, glm::min(p1.x, p2.x), glm::max(p1.x, p2.x)),
                                    glm::clamp(CylinderPos.y, glm::min(p1.y, p2.y), glm::max(p1.y, p2.y)),
                                    glm::clamp(CylinderPos.z, glm::min(p1.z, p2.z), glm::max(p1.z, p2.z)));





    if(glm::abs(glm::length(closesteP-CylinderPos)) <= glm::abs(cylRadius))
    {
        glm::vec3 p2 = (closesteP - CylinderPos);
        if(p2.x == 0.f && p2.y == 0.f && p2.z == 0.f)
        {
            p2.x = 0.0f;
            p2.y = 0.0f;
            p2.z = 0.1f;
        }

        glm::vec3 p = glm::abs(glm::length(closesteP-CylinderPos) - cylRadius) * glm::normalize(p2);

        return p;
    }


    return glm::vec3(-1, -1, -1);
}







void CollisionSystem::onTick(bool* lose)
{
    std::map<std::string, GameObject> objects = m_objects;
    std::map<std::string, GameObject> objects2 = m_objects;


    for (auto& x : objects)
    {

        GameObject obj1 = x.second;

        objects2.erase(x.first);
        if(obj1.isComponent("CollisionComponent"))
        {

                for (auto& y : objects2)
                {
                    //std::cout << y.first << std::endl;
                    GameObject obj2 = y.second;
                    if(obj2.isComponent("CollisionComponent"))
                    {

                        if(!((CollisionComponent*)x.second.getComponent("CollisionComponent"))->wa &&
                                !((CollisionComponent*)y.second.getComponent("CollisionComponent"))->wa)
                        {


                            //case cylinder cylinders
                            if(((CollisionComponent*)x.second.getComponent("CollisionComponent"))->m_type == "cylinder" &&
                                    ((CollisionComponent*)y.second.getComponent("CollisionComponent"))->m_type == "cylinder")
                            {
                                glm::vec3 circPos = ((CollisionComponent*)y.second.getComponent("CollisionComponent"))->circlePos;

                                glm::vec3 b = checkCollisionCylinderCylinder(x.second.getComponent("CollisionComponent"), y.second.getComponent("CollisionComponent"));
                                if(b != glm::vec3(-1.f, -1.f, -1.f))
                                {

                                    //if((x.second.name == "friend" && y.second.name == "enemy") || (y.second.name == "friend" && x.second.name == "enemy"))
                                    //{
                                        (*lose) = true;
                                    //}

                                    if(y.second.isComponent("PlayerControlComponent"))
                                    {
                                        ((CollisionComponent*)x.second.getComponent("CollisionComponent"))->circlePos += b;
                                        ((TransformComponent*)x.second.getComponent("TransformComponent"))->m_loc += b;
                                    }
                                    else if(x.second.isComponent("PlayerControlComponent"))
                                    {
                                        ((CollisionComponent*)y.second.getComponent("CollisionComponent"))->circlePos += b;
                                        ((TransformComponent*)y.second.getComponent("TransformComponent"))->m_loc += b;
                                    }
                                    else
                                    {
                                        ((CollisionComponent*)y.second.getComponent("CollisionComponent"))->circlePos += 0.5f*b;
                                        ((TransformComponent*)y.second.getComponent("TransformComponent"))->m_loc += 0.5f*b;

                                        ((CollisionComponent*)x.second.getComponent("CollisionComponent"))->circlePos += -0.5f*b;
                                        ((TransformComponent*)x.second.getComponent("TransformComponent"))->m_loc += -0.5f*b;
                                    }
                                }





                            }

                            //case cube cylinders
                            else if(((CollisionComponent*)x.second.getComponent("CollisionComponent"))->m_type == "cube" &&
                                    ((CollisionComponent*)y.second.getComponent("CollisionComponent"))->m_type == "cylinder" )
                            {
                                glm::vec3 b = checkCollisionCubeCylinder(x.second.getComponent("CollisionComponent"), y.second.getComponent("CollisionComponent"));

                                if(b != glm::vec3(-1.f, -1.f, -1.f) && ((CollisionComponent*)x.second.getComponent("CollisionComponent"))->portal == "") //&& its not a portal)
                                {
                                    std::cout << "collide!" << std::endl;


                                    if(!((CollisionComponent*)x.second.getComponent("CollisionComponent"))->m_nonMoveable)
                                    {
                                        ((CollisionComponent*)y.second.getComponent("CollisionComponent"))->circlePos += -0.5f*b;
                                        ((TransformComponent*)y.second.getComponent("TransformComponent"))->m_loc += -0.5f*b;

                                        ((CollisionComponent*)x.second.getComponent("CollisionComponent"))->quadPos += 0.5f*b;
                                        ((TransformComponent*)x.second.getComponent("TransformComponent"))->m_loc += 0.5f*b;
                                    }
                                    else
                                    {


                                        ((CollisionComponent*)y.second.getComponent("CollisionComponent"))->circlePos += -b;
                                        ((TransformComponent*)y.second.getComponent("TransformComponent"))->m_loc += -b;

                                        if(x.second.isComponent("PlayerControlComponent"))
                                        {

                                            PlayerControlComponent* pc = ((PlayerControlComponent*)x.second.getComponent("PlayerControlComponent"));
                                            pc->moveBack(b);

                                        }
                                    }




                                }
                            }

                            //case cylinders cube
                            else if(((CollisionComponent*)x.second.getComponent("CollisionComponent"))->m_type == "cylinder" &&
                                    ((CollisionComponent*)y.second.getComponent("CollisionComponent"))->m_type == "cube" )
                            {
                                glm::vec3 b = checkCollisionCubeCylinder(y.second.getComponent("CollisionComponent"), x.second.getComponent("CollisionComponent"));

                                if(b != glm::vec3(-1.f, -1.f, -1.f) && ((CollisionComponent*)y.second.getComponent("CollisionComponent"))->portal == "") //&& its not a portal)
                                {

                                    std::cout << "collide!" << std::endl;

                                    if(!((CollisionComponent*)y.second.getComponent("CollisionComponent"))->m_nonMoveable)
                                    {

                                        ((CollisionComponent*)y.second.getComponent("CollisionComponent"))->quadPos += 0.5f*b;
                                        ((TransformComponent*)y.second.getComponent("TransformComponent"))->m_loc += 0.5f*b;

                                        ((CollisionComponent*)x.second.getComponent("CollisionComponent"))->circlePos += -0.5f*b;
                                        ((TransformComponent*)x.second.getComponent("TransformComponent"))->m_loc += -0.5f*b;

                                    }
                                    else
                                    {
                                          ((CollisionComponent*)x.second.getComponent("CollisionComponent"))->circlePos += -b;
                                          ((TransformComponent*)x.second.getComponent("TransformComponent"))->m_loc += -b;



                                        if(y.second.isComponent("PlayerControlComponent"))
                                        {

                                            PlayerControlComponent* pc = ((PlayerControlComponent*)y.second.getComponent("PlayerControlComponent"));
                                            pc->moveBack(b);

                                        }
                                    }
                                }
                            }

                        }
                        else
                        {

                            onTickWalls(obj1, obj2);
                        }

                    }


            }

        }
    }

//    if(!(*lose))
//    {
//        glm::vec3 p = ((CollisionComponent*)m_objects["cylinder2"].getComponent("CollisionComponent"))->circlePos;
//        ((EnemyResponseComponent*)m_objects["cylinder2"].getComponent("EnemyResponseComponent"))->print(((CollisionComponent*)m_objects["cylinder"].getComponent("CollisionComponent"))->circlePos, p, &p);

//        ((CollisionComponent*)m_objects["cylinder2"].getComponent("CollisionComponent"))->circlePos = p;
//        m_objects["cylinder2"].m_position = p;
//        ((DrawableComponent*)m_objects["cylinder2"].getComponent("DrawableComponent"))->transform->m_loc = p;
//    }



}



void CollisionSystem::onTickWalls(GameObject obj1, GameObject obj2)
{
    CollisionComponent* walls;
    CollisionComponent* obj;
    GameObject wals;
    GameObject objek;


    if(((CollisionComponent*)obj1.getComponent("CollisionComponent"))->wa)
    {
        walls = ((CollisionComponent*)obj1.getComponent("CollisionComponent"));
        obj = ((CollisionComponent*)obj2.getComponent("CollisionComponent"));

        wals = obj1;
        objek = obj2;
    }
    else
    {
        walls = ((CollisionComponent*)obj2.getComponent("CollisionComponent"));
        obj = ((CollisionComponent*)obj1.getComponent("CollisionComponent"));

        wals = obj2;
        objek = obj1;
    }

    //assuming the obj is a cylinder
    if(obj->m_type == "cylinder")
    {
        int j = walls->m_walls.size() - 1;

        for (size_t i = 0; i < walls->m_walls.size(); i++, j--)
        {


            glm::vec3 b = checkCollisionWallCylinder(walls->m_walls[j], obj);

            bool boolin = true;

            //check if the obj collides with a portal
            //if(portals[0] == NULL)
            //{
                int j = 0;
                for(auto x: m_objects)
                {
                    if(x.second.isComponent("CollisionComponent"))
                    {
                        if(((CollisionComponent*)x.second.getComponent("CollisionComponent"))->m_type == "cube")
                        {
                            if(((CollisionComponent*)x.second.getComponent("CollisionComponent"))->portal == "port")
                            {
                                //portals[j] = &x.second;
                                boolin = (checkCollisionCubeCylinder(((CollisionComponent*)x.second.getComponent("CollisionComponent")), obj) == glm::vec3(-1.f, -1.f, -1.f)) && boolin;
                                j++;
                            }
                        }
                    }

                }
            //}


            //bool boolin = (checkCollisionCubeCylinder(((CollisionComponent*)portals[0]->getComponent("CollisionComponent")), obj) == glm::vec3(-1.f, -1.f, -1.f));// ||
                    //checkCollisionCubeCylinder(((CollisionComponent*)portals[1]->getComponent("CollisionComponent")), obj) == glm::vec3(-1.f, -1.f, -1.f));

            //bool boolin = true;




            if(b != glm::vec3(-1.f, -1.f, -1.f) && boolin) // && it does not collide with a portal)
            {
                //std::cout << "Hit!! " << obj->circlePos.x << " " << obj->circlePos.z << " " << std::endl;

                obj->circlePos += -b;
                ((TransformComponent*)objek.getComponent("TransformComponent"))->m_loc += -b;

                if(objek.isComponent("PlayerControlComponent"))
                {
                    PlayerControlComponent* pc = ((PlayerControlComponent*)objek.getComponent("PlayerControlComponent"));
                    pc->moveBack(b);
                }
            }
        }
    }
}






void CollisionSystem::addObj(std::string name, GameObject gameObj)
{
    m_objects[name] = gameObj;

}

void CollisionSystem::remObj(std::string name)
{
    m_objects.erase(name);

}

