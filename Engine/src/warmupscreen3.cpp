#include "warmupscreen3.h"
#define PI 3.14159



warmupscreen3::warmupscreen3() :
  m_camera(nullptr),
  m_accelerationG(-0.07),
  m_velocity(0),
  m_camDistance(5.f),
  m_dx(0),
  m_dy(0),
  mx(0),
  sec(0),
  doub(0)
{
    keys["m_W"] = false;
    keys["m_A"] = false;
    keys["m_S"] = false;
    keys["m_D"] = false;
    keys["m_Shift"] = false;
}

void warmupscreen3::setup(Graphics* g)
{
    m_camera = std::make_shared<Camera>();
    pos = glm::vec3(0, 0, 0);
    m_camera->setLook(glm::vec3(1, -1, 1));
    m_camera->setEye(pos - (m_camDistance * m_camera->getLook()));
    //m_camera->setLook(glm::vec3(1, -0.2, 0));
    g->setCamera(m_camera);

    g->addTexture("Barrel_texture", ":/images/Barrel_texture.png");
    g->addTexture("grass2", ":/images/grass_minecraft.png");
    Material myFourthMaterial;
    Material myFifthMaterial;
    myFourthMaterial.textureName = "Barrel_texture";
    myFifthMaterial.textureName = "grass2";
    g->addMaterial("Barrel_texture", myFourthMaterial);
    g->addMaterial("grass2", myFifthMaterial);
    m_g = g;
}

void warmupscreen3::resize(Graphics* g, int w, int h)
{
    m_camera->setScreenSize(glm::vec2(w, h));
}


void warmupscreen3::tick(float seconds)
{
     sec += seconds;

     float yaw = -m_dx / 1000.f;
     float pitch = -m_dy / 1000.f;
     m_camera->rotate(yaw, pitch);

     m_look = m_camera->getLook();
     m_dir = glm::normalize(glm::vec3(m_look.x, 0, m_look.z)); // forward-backward movement
     m_perp = glm::vec3(m_dir.z, 0, -m_dir.x);  // strafe movement

     m_dx = 0;
     m_dy = 0;







    /** JUMP CODE START**/
    if(pos.y >= 0.f)
    {
        pos = glm::vec3(pos.x, pos.y + m_velocity, pos.z);
    }

    m_velocity = m_velocity + m_accelerationG;

    if(pos.y <= 0.0f)
    {
        m_velocity = 0;
        doub = 0;
        pos = glm::vec3(pos.x, 0.f, pos.z);

    }



    /** JUMP CODE END **/



    /** MOVE CODE STARTS **/
    float speed = 0.1f;

    /** SPRINT CODE STARTS **/
    if(keys["m_shift"])
    {
        speed = 0.2f;
    }
    /** SPRINT CODE ENDS **/

    if(keys["m_W"]) pos+=(m_dir*speed);
    if(keys["m_S"]) pos+=(-m_dir*speed);
    if(keys["m_A"]) pos+=(m_perp*speed);
    if(keys["m_D"]) pos+=(-m_perp*speed);


    m_camera->setEye(pos - (m_camDistance * m_camera->getLook()));

    /** MOVE CODE ENDS **/
}



void warmupscreen3::draw(Graphics* g)
{


    g->clearTransform();
    g->setMaterial("Barrel_texture");


    g->translate(pos);
    g->rotate(-mx/1300.f, m_camera->getUp());
    //g->rotate(-m_dx/50, glm::vec3(0.f, 1.f, 0.f));
    g->scale(1);
    g->drawShape("cylinder");


    g->setMaterial("grass2");
    g->scale(2);
    for(int x = 0; x < 30; x++)
    {
        for(int y = 0; y < 30; y++)
        {
            g->clearTransform();
            g->translate(glm::vec3(x, 0.f, y));            
            g->drawShape("quad");
        }
    }


    /////////////////////////////////////////////////////////

    g->clearTransform();
    g->translate(glm::vec3(0.f, 0.f, 0.f));
    g->scale(300);
    g->rotate((180.f * PI/180.f), glm::vec3(1.f, 0.f, 0.f));
    //printf("%f\n", sec);
    g->setMaterial("sky3");
    g->setTextureRepeat(glm::vec2(1.f, 1.f));
    g->disableBackfaceCulling();
    g->drawShape("sphere");
    g->clearTransform();
    g->enableBackfaceCulling();
    g->setTextureRepeat(glm::vec2(1.f, 1.f));

    /////////////////////////////////////////////////////////



}

void warmupscreen3::onKeyPressed(QKeyEvent*event)
{
    m_look = m_camera->getLook();
    m_dir = glm::normalize(glm::vec3(m_look.x, 0, m_look.z)); // forward-backward movement
    m_perp = glm::vec3(m_dir.z, 0, -m_dir.x);  // strafe movement


    if(event->key() == Qt::Key_W) keys["m_W"] = true;
    if(event->key() == Qt::Key_S) keys["m_S"] = true;
    if(event->key() == Qt::Key_A) keys["m_A"] = true;
    if(event->key() == Qt::Key_D) keys["m_D"] = true;

    /** SPRINT CODE STARTS **/
    if(event->key() == Qt::Key_Shift) keys["m_shift"] = true;
    /** SPRINT CODE ENDS **/




    /** JUMP CODE START**/
    if(event->key() == Qt::Key_Space && (pos.y <= 0.f || doub == 1))
    {

        if(doub == 1)
        {
            m_velocity = 0;
        }
        m_velocity = m_velocity + 0.8;
        //doub++;
    }
    /** JUMP CODE END**/
}

void warmupscreen3::onMouseDragged(QMouseEvent* event, int dx, int dy)
{
    //m_camera->rotate(-dx / 1000.f, -dy / 1000.f);

    //m_camera->setLook(glm::vec3(m_camera->getLook()));
    mx += dx;
    m_dx = dx;
    m_dy = dy;


}

void warmupscreen3::keyRepeatEvent(QKeyEvent *event)
{



}


void warmupscreen3::keyReleaseEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_W) keys["m_W"] = false;
    if(event->key() == Qt::Key_S) keys["m_S"] = false;
    if(event->key() == Qt::Key_A) keys["m_A"] = false;
    if(event->key() == Qt::Key_D) keys["m_D"] = false;

    /** SPRINT CODE STARTS **/
    if(event->key() == Qt::Key_Shift) keys["m_shift"] = false;
    /** SPRINT CODE ENDS **/
}


void warmupscreen3::releaseKeys()
{

    keys["m_W"] = false;
    keys["m_S"] = false;
    keys["m_A"] = false;
    keys["m_D"] = false;
    keys["m_shift"] = false;

}

std::shared_ptr<Camera> warmupscreen3::getCam()
{
    return m_camera;
}





