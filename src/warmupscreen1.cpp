#include "warmupscreen1.h"





warmupScreen1::warmupScreen1() :
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

void warmupScreen1::setup(Graphics* g)
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

void warmupScreen1::resize(Graphics* g, int w, int h)
{
    m_camera->setScreenSize(glm::vec2(w, h));
}


void warmupScreen1::tick(float seconds)
{
    //std::cout << m_sec << std::endl;
    m_sec += seconds;
}

void warmupScreen1::draw(Graphics* g)
{

    m_camera->setUI(true);



    //health bar
    g->setMaterial(g->getMaterial("boring Green"));

    g->setCamera(m_camera);
    g->clearTransform();



    glm::vec4 r1 = glm::vec4(0.5  , 0  , 0  , 0  );
    glm::vec4 r2 = glm::vec4(0  , 0.5  , 0  , 0  );
    glm::vec4 r3 = glm::vec4(0  , 0  , 0.5  , 0  );
    glm::vec4 r4 = glm::vec4(0.5  , 0.5  , 0  , 1  );

    g->setTransform(glm::mat4(r1, r2, r3, r4));


    g->drawShape("cube");




}

void warmupScreen1::onKeyPressed(QKeyEvent*event)
{

}

void warmupScreen1::onMouseDragged(QMouseEvent* event, int dx, int dy)
{
    //m_camera->rotate(-dx / 1000.f, -dy / 1000.f);
}

void warmupScreen1::keyRepeatEvent(QKeyEvent *event)
{



}


void warmupScreen1::keyReleaseEvent(QKeyEvent *event)
{


}

std::shared_ptr<Camera> warmupScreen1::getcam()
{
    return m_camera;
}

void warmupScreen1::releaseKeys()
{

    keys["m_W"] = false;
    keys["m_S"] = false;
    keys["m_A"] = false;
    keys["m_D"] = false;
    keys["m_shift"] = false;

}




