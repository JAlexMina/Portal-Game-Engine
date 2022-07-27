#include "warmupscreen2.h"





warmupscreen2::warmupscreen2() :
m_camera(nullptr),
m_accelerationG(0),
m_velocity(0),
m_sec(0)
{
    keys["m_W"] = false;
    keys["m_A"] = false;
    keys["m_S"] = false;
    keys["m_D"] = false;
    keys["m_Shift"] = false;
}

void warmupscreen2::setup(Graphics* g)
{
    m_camera = std::make_shared<Camera>();
    m_camera->setEye(glm::vec3(2, 20, 2));
    m_camera->setLook(glm::vec3(0, -1, 0));

    g->setCamera(m_camera);


    Material myFirstMaterial;
    myFirstMaterial.color = glm::vec3(0.5f, 0.75f, 0.5f);
    g->addMaterial("boringGreen", myFirstMaterial);



    g->addTexture("Barrel_texture", ":/images/Barrel_texture.png");
    g->addTexture("grass2", ":/images/grass_minecraft.png");
    Material myFourthMaterial;
    Material myFifthMaterial;
    myFourthMaterial.textureName = "Barrel_texture";
    myFifthMaterial.textureName = "grass2";
    g->addMaterial("Barrel_texture", myFourthMaterial);
    g->addMaterial("grass2", myFifthMaterial);

}

void warmupscreen2::resize(Graphics* g, int w, int h)
{
    m_camera->setScreenSize(glm::vec2(w, h));
}


void warmupscreen2::tick(float seconds)
{
    //std::cout << m_sec << std::endl;
    m_sec += seconds;
}

void warmupscreen2::draw(Graphics* g)
{

    g->setMaterial("boringGreen");
    g->translate(glm::vec3(0.f, 0.f, 0.f));
    g->scale(30);
    //g->drawShape("quad");
    g->clearTransform();
    g->rotate(5, glm::vec3(1.f, 0.f, 0.f));
    g->translate(glm::vec3(3.f, 0.f, 0.f));
    g->rotate(m_sec, glm::vec3(0.f, 0.f, 1.f));
    g->setMaterial("Barrel_texture");
    g->drawText("PAUSE", 3);
    g->clearTransform();




//    g->setMaterial("grass2");
//    //g->setMaterial("no-Image");
//    g->scale(2);
//    for(int x = 0; x < 12; x++)
//    {
//        for(int y = 0; y < 12; y++)
//        {
//            g->clearTransform();
//            g->translate(glm::vec3(x, 0.f, y));
//            g->drawShape("quad");
//        }
//    }

}

void warmupscreen2::onKeyPressed(QKeyEvent*event)
{

}

void warmupscreen2::onMouseDragged(QMouseEvent* event, int dx, int dy)
{
    //m_camera->rotate(-dx / 1000.f, -dy / 1000.f);
}

void warmupscreen2::keyRepeatEvent(QKeyEvent *event)
{



}


void warmupscreen2::keyReleaseEvent(QKeyEvent *event)
{


}

std::shared_ptr<Camera> warmupscreen2::getcam()
{
    return m_camera;
}

void warmupscreen2::releaseKeys()
{

    keys["m_W"] = false;
    keys["m_S"] = false;
    keys["m_A"] = false;
    keys["m_D"] = false;
    keys["m_shift"] = false;

}




