#include "Chunk.h"
#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>
#include "engine/graphics/Shape.h"
#include <bits/stdc++.h>


Chunk::Chunk()
{

}


bool Chunk::isInBounds(int x, int y)
{
    if(x >= 0 && x < sizeOfChunk)
    {
        if(y >= 0 && y < sizeOfChunk)
        {
            return true;
        }
    }
    return false;
}


bool Chunk::isMiddle(int x)
{
    return (sizeOfChunk - (x+1) == x);
}


//Drunken Walk Algo
void Chunk::makeChunk(int x, int y, int seed)
{
    Room* curr = &rooms[x][y];
    curr->visited = true;


      std::vector<int> myvector;

      // set some values:
      for (int i = 0; i <= 3; ++i) myvector.push_back(i); // 0 1 2 3

      // using built-in random generator:
      std::shuffle ( myvector.begin(), myvector.end(), std::default_random_engine(seed) );
      int direct = 0;

    if(nW > 0)
    {
          //std::cout << nW << std::endl;
    }

    for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    {
        direct = *it;

        switch(direct)
        {
            case NORTH:
            {
                int ns = NORTH;
                int nsOp = SOUTH;
                int yo = -1;

                if(isInBounds(x, y+yo) || (isMiddle(x) && !isInBounds(x, y+yo)))
                {

                    if((isMiddle(x) && !isInBounds(x, y+yo)))
                    {

                        curr->walls[ns] = 0;
                    }
                    else
                    {


                        Room* currNeighbor = &rooms[x][y+yo];
                        if(!currNeighbor->visited)
                        {
                             curr->walls[ns] = 0;

                                makeChunk(x, y+yo, seed+1);

                        }
                        else if(!currNeighbor->walls[nsOp])
                        {
                            curr->walls[ns] = 0;
                        }
                        else
                        {
                            curr->walls[ns] = 1;
                            nW++;
                        }
                    }
                }
                else
                {
                    curr->walls[ns] = 1;
                    nW++;
                }
                break;
            }

            case SOUTH:
            {
                int ns = SOUTH;
                int nsOp = NORTH;
                int yo = 1;

                if(isInBounds(x, y+yo) || (isMiddle(x) && !isInBounds(x, y+yo)))
                {

                    if((isMiddle(x) && !isInBounds(x, y+yo)))
                    {

                        curr->walls[ns] = 0;
                    }
                    else
                    {


                        Room* currNeighbor = &rooms[x][y+yo];
                        if(!currNeighbor->visited)
                        {
                             curr->walls[ns] = 0;

                             makeChunk(x, y+yo, seed+2);

                        }
                        else if(!currNeighbor->walls[nsOp])
                        {
                            curr->walls[ns] = 0;
                        }
                        else
                        {
                            curr->walls[ns] = 1;
                            nW++;
                        }
                    }
                }
                else
                {
                    curr->walls[ns] = 1;
                    nW++;
                }
                break;
            }

            case EAST:
            {
                int ns = EAST;
                int nsOp = WEST;
                int xo = 1;

                if(isInBounds(x+xo, y) || (isMiddle(y) && !isInBounds(x+xo, y)))
                {

                    if((isMiddle(y) && !isInBounds(x+xo, y)))
                    {

                        curr->walls[ns] = 0;
                    }
                    else
                    {

                        Room* currNeighbor = &rooms[x+xo][y];
                        if(!currNeighbor->visited)
                        {
                            curr->walls[ns] = 0;

                            makeChunk(x+xo, y, seed+3);

                        }
                        else if(!currNeighbor->walls[nsOp])
                        {
                            curr->walls[ns] = 0;
                        }
                        else
                        {
                            curr->walls[ns] = 1;
                            nW++;
                        }
                    }
                }
                else
                {
                    curr->walls[ns] = 1;
                    nW++;
                }
                break;
            }

            case WEST:
            {
                int ns = WEST;
                int nsOp = EAST;
                int xo = -1;

                if(isInBounds(x+xo, y) || (isMiddle(y) && !isInBounds(x+xo, y)))
                {

                    if((isMiddle(y) && !isInBounds(x+xo, y)))
                    {

                        curr->walls[ns] = 0;
                    }
                    else
                    {

                        Room* currNeighbor = &rooms[x+xo][y];
                        if(!currNeighbor->visited)
                        {
                            curr->walls[ns] = 0;

                            makeChunk(x+xo, y, seed+4);

                        }
                        else if(!currNeighbor->walls[nsOp])
                        {
                            curr->walls[ns] = 0;
                        }
                        else
                        {
                            curr->walls[ns] = 1;
                            nW++;
                        }
                    }
                }
                else
                {
                    curr->walls[ns] = 1;
                    nW++;
                }
                break;
            }
        }
    }

}




//Cross Product
glm::vec3 cross(glm::vec3 v1, glm::vec3 v2)
{
    float cx = v1.y * v2.z - v1.z * v2.y;
    float cy = v1.z * v2.x - v1.x * v2.z;
    float cz = v1.x * v2.y - v1.y * v2.x;

    return glm::vec3(cx, cy, cz);
}





std::shared_ptr<Shape> Chunk::makeShape(bool floor)
{


    std::vector<float> v;
    std::vector<int> f;
    const std::shared_ptr<Shape> cu = std::shared_ptr<Shape> (new Shape(v, f));
    int ii = 0;

    int xio = 0;
    int yio = 0;
    float zed = 0;
    float ex = 0;
    float m = 1;

    if(!floor)
    {

        for(xio = 0; xio < sizeOfChunk; xio++)
        {
            for(yio = 0; yio < sizeOfChunk; yio++)
            {
                for(int i = 0; i <= 3; i++ )
                {
                    cube* r = new cube();

                    int j = 0;

                    if(i == 0)
                    {
                        j = 0;
                    }
                    else if (i == 1)
                    {
                        j = 2;
                    }
                    else if (i == 2)
                    {
                        j = 1;
                    }
                    else
                    {
                      j = 3;
                    }


                    int w = rooms[yio][xio].walls[j];

                    //if there is a wall
                    if (w)
                    {


                        float x = 0;
                        float y = ydim;
                        float z = 0;

                        //NORTH
                        if(i == 0)
                        {
                            z = 0 + yio*dim;
                            x = 0 + xio*dim;
                            zed = dim;
                            ex = 0;
                            m = 1;
                        }

                        //SOUTH
                        else if(i == 1)
                        {
                            z = dim +  yio*dim;
                            x = 0  +  xio*dim;
                            zed = 0;
                            ex = dim;
                            m = -1;
                        }

                        //EAST
                        else if(i == 2)
                        {
                            z = dim + yio*dim;
                            x = dim + xio*dim;
                            zed = -dim;
                            ex = 0;
                            m = -1;
                        }

                        //WEST
                        else
                        {
                            z = 0 +  yio*dim;
                            x = dim + xio*dim;
                            zed = 0;
                            ex = -dim;
                            m = 1;
                        }


                        (*r).width = dim;
                        (*r).height = dim;

                        float s, t = 0.f;
                        s = (0.f/2.f);
                        t = (0);

                        glm::vec3 norm = m * glm::normalize(glm::cross(glm::vec3(x, y, z) - glm::vec3(x+ex, y   , z+zed), glm::vec3(x, y, z) - glm::vec3(x   , y-dim, z)));
                        float n1, n2, n3 = 0.f;
                        n1 = norm[0];
                        n2 = norm[1];
                        n3 = norm[2];

                        if(i  <= 3 )
                        {
                            (*r).p1 = glm::vec3(x, 0, z);
                            (*r).p2 = glm::vec3(x+ex, 0, z+zed);



                            (*cu).addVertex(x   , y   , z    , n1, n2, n3, s, t);
                            (*cu).addVertex(x   , y-ydim, z    , n1, n2, n3, s, t+(1.f));

                            (*cu).addVertex(x+ex, y   , z+zed, n1, n2, n3, s+(1.f/2.f), t);
                            (*cu).addVertex(x+ex, y-ydim, z+zed, n1, n2, n3, s+(1.f/2.f), t+(1.f));


                            (*cu).addFace(ii, ii+2, ii+1);
                            (*cu).addFace(ii+1, ii+2, ii+3);
                                ii = ii + 4;


                            auto it = std::find(m_walls.begin(), m_walls.end(), (*r));

                            if (it != m_walls.end())
                            {

                            }
                            else
                            {
                                m_walls.push_back((*r));
                            }

                            free(r);

                        }



                    } //if there is a wall ^^

                } //for every room side ^^



            } // for every room y ^^
        } // for every room x ^^

    }

    //ADDING THE FLOOR
    if(floor)
    {
        float s, t = 0.f;
        s = (1.f/2.f);
        t = (0);


        (*cu).addVertex( 0, 0, 0, 0, 1, 0, s, t);
        (*cu).addVertex(0, 0 , (sizeOfChunk * dim) , 0, 1, 0, s, t+(1.f));

        (*cu).addVertex((sizeOfChunk * dim), 0 , 0, 0, 1, 0, s+(1.f/2.f), t);
        (*cu).addVertex((sizeOfChunk * dim), 0 , (sizeOfChunk * dim), 0, 1, 0, s+(1.f/2.f), t+(1.f));



        (*cu).addFace(ii, ii+1, ii+2);
        (*cu).addFace(ii+1, ii+3, ii+2);
    }


    return cu;
}






void Chunk::printChunk()
{
    for (int x = 0; x < sizeOfChunk; x++)
    {
        for (int y = 0; y < sizeOfChunk; y++)
        {
            Room* curr = &rooms[x][y];
            std::cout << "x("<< x << ") y(" << y <<  ") ";


            for (int i = 0; i <= 3; i++)
            {
                std::cout << curr->walls[i] << " ";

            }

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}


