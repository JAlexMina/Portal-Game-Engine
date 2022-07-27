#include "PlayerControlComponent.h"
#include "engine/graphics/Camera.h"

PlayerControlComponent::PlayerControlComponent() :
    cam_velocity(0),
    m_dx(0),
    m_dy(0)
{
    keys["m_W"] = false;
    keys["m_A"] = false;
    keys["m_S"] = false;
    keys["m_D"] = false;
    keys["m_Shift"] = false;
}

void PlayerControlComponent::onKeyPress(QKeyEvent*event)
{
    if(event->key() == Qt::Key_W) keys["m_W"] = true;
    if(event->key() == Qt::Key_S) keys["m_S"] = true;
    if(event->key() == Qt::Key_A) keys["m_A"] = true;
    if(event->key() == Qt::Key_D) keys["m_D"] = true;

    /** SPRINT CODE STARTS **/
    if(event->key() == Qt::Key_Shift) keys["m_shift"] = true;
    /** SPRINT CODE ENDS **/

//    if(event->key() == Qt::Key_P)
//    {
//        (*isThirdPerson) = !(*isThirdPerson);
//    }



    /** JUMP CODE START**/
    if(event->key() == Qt::Key_Space && m_camera->m_pos.y <= 2.5f)
    {

        cam_velocity = cam_velocity + 0.8f;

    }
    /** JUMP CODE END**/
}



void PlayerControlComponent::onKeyRelease(QKeyEvent*event)
{
    if(event->key() == Qt::Key_W) keys["m_W"] = false;
    if(event->key() == Qt::Key_S) keys["m_S"] = false;
    if(event->key() == Qt::Key_A) keys["m_A"] = false;
    if(event->key() == Qt::Key_D) keys["m_D"] = false;

    /** SPRINT CODE STARTS **/
    if(event->key() == Qt::Key_Shift) keys["m_shift"] = false;
    /** SPRINT CODE ENDS **/

}

void PlayerControlComponent::onTick(std::shared_ptr<Camera> camera, bool*isThirdPerson)
{
    itp = isThirdPerson;
    m_camera = camera;


    float yaw = -m_dx / 1000.f;
    float pitch = -m_dy / 1000.f;
    camera->rotate(yaw, pitch);

    m_look = camera->getLook();
    m_dir = glm::normalize(glm::vec3(m_look.x, 0, m_look.z)); // forward-backward movement
    m_perp = glm::vec3(m_dir.z, 0, -m_dir.x);  // strafe movement

    m_dx = 0;
    m_dy = 0;

    //camera->m_pos.y = 100; //  <------- undo this later please, thank you future me!!

    if(*isThirdPerson)
    {
        //std::cout << pos.y << " <-y pos " << cam_velocity << " <-vel " << std::endl;
        if(pos.y > 2.5f)
        {
            cam_velocity = cam_velocity + GRAVITY;
        }

        pos = (glm::vec3(pos.x, pos.y + cam_velocity, pos.z));



        if(pos.y < 2.5f)
        {
            //std::cout << "in" << std::endl;
            cam_velocity = 0;
            pos = (glm::vec3(pos.x, 2.5f, pos.z));
        }
    }
    else
    {
        //std::cout << pos.y << " <-y pos " << cam_velocity << " <-vel " << std::endl;
        if(camera->m_pos.y > 2.5f)
        {
            cam_velocity = cam_velocity + GRAVITY;
        }

        pos = (glm::vec3(pos.x, pos.y + cam_velocity, pos.z));


        if(pos.y <= 2.5f)
        {
            //std::cout << "in" << std::endl;
            cam_velocity = 0;
            pos = (glm::vec3(camera->m_pos.x, 2.5f, camera->m_pos.z));
        }
    }


    float tot = 0;


    if(keys["m_W"])
    {
        tot++;
    }
    if(keys["m_S"])
    {
        tot++;
    }
    if(keys["m_A"])
    {
        tot++;
    }
    if(keys["m_D"])
    {
        tot++;
    }





    float speed = 0.2f/tot;


    if(keys["m_shift"])
    {
        speed = 0.4f/tot;
    }


    if(!wall)
    {

        if(keys["m_W"])
        {
            pos+=(m_dir*speed);
        }
        if(keys["m_S"])
        {
            pos+=(-m_dir*speed);
        }
        if(keys["m_A"])
        {
            pos+=(m_perp*speed);
        }
        if(keys["m_D"])
        {
            pos+=(-m_perp*speed);
        }
    }




    if(!(*isThirdPerson))
    {

        camera->setEye( camera->m_pos);
        //pos = camera->m_pos;
    }
    else
    {

        //camera->setEye(camera->m_pos - (6.f * camera->getLook()));

        glm::vec3 a = glm::vec3(pos - (6.f * m_camera->getLook()));
        m_camera->setEye(glm::vec3(a.x, a.y + 0.75f, a.z));
//        pos = camera->m_pos;
        //camera->m_pos = pos;
        //camera->m_pos = glm::vec3(camera->m_pos.x, camera->m_pos.y - 2.5f, camera->m_pos.z);

    }

    camera->m_pos = pos;



}

void PlayerControlComponent::moveBack(glm::vec3 m)
{
    pos += (-m);
    //m_camera->m_pos += (-m);

    if(!(*itp))
    {

        m_camera->setEye( m_camera->m_pos);
        //pos = m_camera->m_pos;
    }
    else
    {
        glm::vec3 a = glm::vec3(pos - (6.f * m_camera->getLook()));
        m_camera->setEye(glm::vec3(a.x, a.y + 0.75, a.z));
        //pos = m_camera->m_pos;
        //camera->m_pos = glm::vec3(camera->m_pos.x, camera->m_pos.y - 2.5f, camera->m_pos.z);

    }
    m_camera->m_pos = pos;
}

void PlayerControlComponent::onMouseDragged(QMouseEvent* event, int dx, int dy)
{

    mx += dx;
    m_dx = dx;
    m_dy = dy;

}


void PlayerControlComponent::releaseKeys()
{

    keys["m_W"] = false;
    keys["m_S"] = false;
    keys["m_A"] = false;
    keys["m_D"] = false;
    keys["m_shift"] = false;

}
