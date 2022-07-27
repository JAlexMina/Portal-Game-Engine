#include "Wander.h"
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>
#include <bits/stdc++.h>
#include "CollisionComponent.h"
#include "drawablecomponent.h"

Wander::Wander()
{

}

Status Wander::update(float seconds)
{

}

void Wander::reset()
{

}


std::string Wander::wanderingAction(GameObject* strOBJ, glm::vec3* startPos)
{


    if(!(*strOBJ).goen)
    {
        int x = (int)glm::floor((*strOBJ).m_position.x/sizeOfRoom);
        int y = (int)glm::floor((*strOBJ).m_position.z/sizeOfRoom);
        //srand (time(NULL));
        int internationalHouseOfPancakes = rand() % 1000;

        (*strOBJ).r = wander(rooms[x][y], rooms[x][y].l, internationalHouseOfPancakes);

        //std::cout << strOBJ.second.r.l << std::endl;



        //std::cout << strOBJ.second.r.x << " " << strOBJ.second.r.y << std::endl;
        (*strOBJ).oldp = (*strOBJ).m_position;

    }

    going(&(*strOBJ), (*strOBJ).r, (*startPos));


    return "RUNNING";
}




void Wander::setRooms(Room r[sizeOfChunk][sizeOfChunk])
{
    for (int x = 0; x < sizeOfChunk; x++)
    {
        for (int y = 0; y < sizeOfChunk; y++)
        {
            rooms[x][y] = r[y][x];

            rooms[x][y].x = x;
            rooms[x][y].y = y;
        }
    }
}


void Wander::going(GameObject* obj, Room goTo, glm::vec3 startingPos)
{
    float x = startingPos.x + goTo.x*((float)sizeOfRoom) + 0.5f*((float)sizeOfRoom);
    float z = startingPos.z + goTo.y*((float)sizeOfRoom) + 0.5f*((float)sizeOfRoom);

    //std::cout << goTo.x << " " << goTo.y << std::endl;
    //std::cout << x << " " << z << std::endl;

    (*obj).m_position = (*obj).m_position + (0.01f)*((glm::vec3(x, 0, z) - (*obj).oldp));
    ((DrawableComponent*)(*obj).getComponent("DrawableComponent"))->transform->m_loc = (*obj).m_position;
    ((CollisionComponent*)(*obj).getComponent("CollisionComponent"))->circlePos = (*obj).m_position;


    //std::cout << x << std::endl;

    if(glm::abs((*obj).m_position.x - x) < 0.001f && glm::abs((*obj).m_position.z - z) < 0.001f)
    {
        (*obj).goen = false;
        //std::cout << "next" << std::endl;
    }
    else
    {
        (*obj).goen = true;
    }

}





//a function that given a room and an int (0 = N, 1 = S, 2 = East, 3 = West)
//corresponding to where you came from, it will randomly return a room that
//you can go into, it will not go back unless it has to.
Room Wander::wander(Room curr, int last, int seed)
{
    std::vector<int> myvector;
    Room r;



    // set some values:
    for (int i = 0; i <= 3; ++i) myvector.push_back(i); // 0 1 2 3

    // using built-in random generator:
    std::shuffle ( myvector.begin(), myvector.end(), std::default_random_engine(seed));
    int i = 0;
    for(auto& vc : myvector)
    {
        if (vc == last)
        {

            myvector.erase(myvector.begin()+i);

        }
        i++;
    }

    myvector.push_back(last);


//    for(auto& v : myvector)
//    {
//        std::cout << v << " ";
//    }
//    std::cout << std::endl;



    //looping through the walls
    for(int i = 0; i < 4; i++)
    {
        //std::cout << std::endl;
        //std::cout << curr.walls[myvector[i]] << std::endl;

            //if there is not a wall
            if(!curr.walls[myvector[i]])
            {
                //std::cout << myvector[i] << std::endl;


                switch(myvector[i])
                {
                    case 0:
                    {
                        rooms[curr.x-1][curr.y].l = 1;
                        return rooms[curr.x-1][curr.y];
                    }
                    case 1:
                    {
                        rooms[curr.x+1][curr.y].l = 0;
                        return rooms[curr.x+1][curr.y];
                    }
                    case 2:
                    {

                        rooms[curr.x][curr.y+1].l = 3;
                        return rooms[curr.x][curr.y+1];
                    }
                    case 3:
                    {
                        rooms[curr.x][curr.y-1].l = 2;
                        return rooms[curr.x][curr.y-1];
                    }

                }
            }


    }





}
