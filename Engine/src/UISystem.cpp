#include "UISystem.h"


UISystem::UISystem()

{

}


glm::vec3 UISystem::convertToScreenSpace(glm::vec3 pos, glm::vec2 screenSize)
{

    // get these from your camera
//    glm::mat4x4 projection = m_camera->getUIProjection();
//    glm::mat4x4 view = m_camera->getUIView();

    glm::mat4x4 projection = m_camera->getProjection();
    glm::mat4x4 view = m_camera->getView();

    // this is necessary for the matrix multiplication
    glm::vec4 fourVec = glm::vec4(pos.x, pos.y, pos.z, 1.f);

    // project the position into clip space
    fourVec = projection * view * fourVec;

    // x and y range from -1 to 1
    glm::vec3 clipSpace = glm::vec3(fourVec.x / fourVec.w, fourVec.y / fourVec.w, fourVec.z);

    // convert x and y to pixel coordinates, leave z alone
    return glm::vec3((clipSpace.x + 1) * .5f * screenSize.x, (1 + clipSpace.y) * .5f * screenSize.y, clipSpace.z);

//    float y = (clipSpace.y) * screenSize.y;
//    y = y - (screenSize.y/2.f);
//    if(y < 0)
//    {
//        y = 0;
//    }

//    y += (screenSize.y/2.f);

//    return glm::vec3((clipSpace.x + 1) * .5f * screenSize.x, y, clipSpace.z);

}



void UISystem::setup(std::shared_ptr<Camera> camera, Graphics* g)
{
    m_camera = camera;
    m_g = g;

    glm::vec3 c = glm::vec3(0.4f, 0.65f, 0.4f);
    addMaterial(m_g, "boring Green", c);


    c = glm::vec3(0.0f, 0.0f, 0.0f);
    addMaterial(m_g, "black", c);

}

void UISystem::addMaterial(Graphics* g, std::string name, glm::vec3 color)
{
    Material m_material;
    m_material.color = color;
    g->addMaterial(name, m_material);
}


void UISystem::draw2D(glm::vec3 pos)
{
    m_camera->setUI(true);



    //health bar
    m_g->setMaterial(m_g->getMaterial("boring Green"));

    m_g->setCamera(m_camera);
    m_g->clearTransform();



    glm::vec4 r1 = glm::vec4(0.5  , 0  , 0  , 0  );
    glm::vec4 r2 = glm::vec4(0  , 0.02  , 0  , 0  );
    glm::vec4 r3 = glm::vec4(0  , 0  , 0.5  , 0  );
    glm::vec4 r4 = glm::vec4(0.5  , 0.01  , 0  , 1  );

    m_g->setTransform(glm::mat4(r1, r2, r3, r4));


    m_g->drawShape("cube");





    //word health
    m_g->clearTransform();
    m_g->setMaterial(m_g->getMaterial("black"));




    r1 = glm::vec4(1  , 0  , 0  , 0  );
    r2 = glm::vec4(0  , 1  , 0  , 0  );
    r3 = glm::vec4(0  , 0  , 1  , 0  );
    r4 = glm::vec4(0.30  , 0.03  , 0  , 1  );

    m_g->setTransform(glm::mat4(r1, r2, r3, r4));

    m_g->drawText("Health", 0.05f);







    //above the cylinder
    m_g->clearTransform();
    m_g->setMaterial(m_g->getMaterial("boring Green"));

    glm::vec3 possy = glm::vec3(pos.x, pos.y + 3, pos.z);


    glm::vec3 p = convertToScreenSpace(possy, m_g->sizeOfViewport);



    float dist = glm::abs(glm::length(m_camera->getEye() - pos));

    //std::cout << 1/dist << std::endl;

    float x = 1/dist + 0.10;


    r1 = glm::vec4(x  , 0  , 0  , 0  );
    r2 = glm::vec4(0  , 0.08*x , 0  , 0  );
    r3 = glm::vec4(0  , 0  , 0.25  , 0  );
    r4 = glm::vec4(p.x/m_g->sizeOfViewport.x  , p.y/m_g->sizeOfViewport.y  , 0  , 1  );

    m_g->setTransform(glm::mat4(r1, r2, r3, r4));


    if(p.z > 0)
        m_g->drawShape("cube");



    m_camera->setUI(false);
}


