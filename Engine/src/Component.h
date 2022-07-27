#ifndef COMPONENT_H
#define COMPONENT_H

#define GRAVITY -0.07

#include "engine/graphics/Graphics.h"
//#include "CollisionComponent.h"

class GameObject;




class Component
{
public:
    Component();
    //virtual ~Component();
    void onTick(float seconds);


    void onDrawer(Graphics* g) {
        //std::cout << "1.1" << std::endl;
        onDraw(g);
    }



    void transformer(Graphics* g)
    {
        transform(g);
    }







    GameObject *m_gameObject;

private:
    virtual void onDraw(Graphics* g);
    virtual void transform(Graphics* g);


};


#endif // COMPONENT_H
