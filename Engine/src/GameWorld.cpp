#include "GameWorld.h"
#include "CollisionComponent.h"
#include "Chunk.h"
#include "engine/graphics/Shape.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Texture2D.h"
#include <algorithm>
#include "CollisionComponent.h"
#include <stdlib.h>
#include "engine/graphics/ResourceLoader.h"
#include "engine/graphics/FBO.h"
#include "engine/graphics/ResourceLoader.h"

#include "engine/graphics/IBO.h"
#include "engine/graphics/VBOAttribMarker.h"
#include "engine/graphics/ShaderAttribLocations.h"
#include "engine/graphics/Graphics.h"

#include <cstdarg>


GameWorld::GameWorld() :
    sec(0),
     m_isThirdPerson(false),
    lose(false),
    win(false)//,m_blurFBO1(nullptr)
{

}



void GameWorld::setup(Graphics* g)
{

    // Create shader programs.
    m_normProgram = ResourceLoader::loadShaders(
                ":/shaders/shader.vert", ":/shaders/shader.frag");
    m_portalProgram = ResourceLoader::loadShaders(
                ":/shaders/portal.vert", ":/shaders/portal.frag");





    std::shared_ptr<FBO> sti (new FBO(g->sizeOfViewport.x, g->sizeOfViewport.y));
    //m_blurFBO1  = sti;


    Material myFirstMaterial;
    myFirstMaterial.color = glm::vec3(0.8f, 0.0f, 0.0f);
    g->addMaterial("red", myFirstMaterial);


    g->addTexture("stoneNew", ":/images/marble.png");
    Material terrainM;
    terrainM.textureName = "stoneNew";
    g->addMaterial("stoneNew", terrainM);
    g->getTexture("stoneNew")->setFilterMethod(Texture::FILTER_METHOD::NEAREST);



    g->addTexture("stoneFloor", ":/images/COLORED_2.jpg");
    Material terrainFloor;
    terrainFloor.textureName = "stoneFloor";
    g->addMaterial("stoneFloor", terrainFloor);
    g->getTexture("stoneFloor")->setFilterMethod(Texture::FILTER_METHOD::NEAREST);


    //setting up the camera
    m_camera = std::make_shared<Camera>();
    m_camera1 = std::make_shared<Camera>();
    m_camera2 = std::make_shared<Camera>();





    m_camera->setEye(glm::vec3(2.f, 2.5f, 2.f));
    m_camera->setLook(glm::vec3(1, 0, 1));
    g->setCamera(m_camera);


    m_camera->m_pos = m_camera->getEye();

    camera.m_position = m_camera->getEye();


    //cylinderEnemy.name = "enemy";
    cylinder.name = "friend";
    camera.name = "player";


    std::shared_ptr<Shape> s;
    std::shared_ptr<Shape> t;


    std::string file = ":/OBJs/natkins.obj";
    QString obj(QString::fromStdString(file));
    t = ResourceLoader::readObj(obj, s);

    //std::cout << t->getNumVerts() << std::endl;


    g->addShape("enemy", t);



    //adding drawable component



//    drawCylinderEnemy = new DrawableComponent (":/images/no-Image.png", "no-Image", "enemy", g);
//    cylinderEnemy.m_position = glm::vec3(5.f, 3.f, 5.f);
//    drawCylinderEnemy->transform = new TransformComponent (cylinderEnemy.m_position , 2.5f);
//    cylinderEnemy.addComponent(drawCylinderEnemy->transform, "TransformComponent");
//    cylinderEnemy.addComponent(drawCylinderEnemy, "DrawableComponent");

//    CylinderEnemyAI = new PathFinderComponent(false, glm::vec3());
//    cylinder.addComponent(CylinderEnemyAI, "PathFinderComponent");



    drawCylinder = new DrawableComponent (":/images/Barrel_texture.png", "barrel", "cylinder", false);
    cylinder.m_position = glm::vec3(3.f, 0.f, 5.f);
    drawCylinder->transform = new TransformComponent (cylinder.m_position , 1.5f);
    cylinder.addComponent(drawCylinder->transform, "TransformComponent");
    cylinder.addComponent(drawCylinder, "DrawableComponent");

    drawCylinderShadow = new DrawableComponent (":/images/Barrel_texture.png", "barrel", "cylinder", false);
    cylinderShadow.m_position = glm::vec3(3.f, 0.f, 5.f);
    drawCylinderShadow->transform = new TransformComponent (cylinderShadow.m_position , 1.5f);
    cylinderShadow.addComponent(drawCylinderShadow->transform, "TransformComponent");
    cylinderShadow.addComponent(drawCylinderShadow, "DrawableComponent");


    drawCylinderPlayer = new DrawableComponent (":/images/sky.png", "sky", "cylinder", false);
    drawCylinderPlayer->transform = new TransformComponent (camera.m_position , 1.5f);
    camera.addComponent(drawCylinderPlayer->transform, "TransformComponent");
    camera.addComponent(drawCylinderPlayer, "DrawableComponent");



    //adding collision component
    collideCylinder = new CollisionComponent (cylinder.m_position, 0.733333f, 2.f, "cylinder", false, m_camera);
    cylinder.addComponent(collideCylinder, "CollisionComponent");

    collideCylinderShadow = new CollisionComponent (cylinderShadow.m_position, 0.733333f, 2.f, "cylinder", false, m_camera);
    cylinderShadow.addComponent(collideCylinderShadow, "CollisionComponent");

    camera.addComponent(&pc, "PlayerControlComponent");


    //adding collision component
//    collideCylinderEnemy = new CollisionComponent (cylinderEnemy.m_position, 0.7333333f, 2.f, "cylinder", false, m_camera);
//    cylinderEnemy.addComponent(collideCylinderEnemy, "CollisionComponent");







    collideCam = new CollisionComponent (m_camera->getEye(), 1.f, 4.f, "cylinder", false, m_camera);
    camera.addComponent(collideCam, "CollisionComponent");


    //adding objs to gameworld list of objs
    m_objects["cylinder"] = cylinder;
    m_objects["cylinderShadow"] = cylinderShadow;
    m_objects["cylinder3"] = camera;



    //Portal Objects \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


    //frame of 1
    drawPortal1frame = new DrawableComponent (":/images/CORRED_1.jpg", "portal1frame", "cube", false);
    Portal1frame.m_position = glm::vec3(6.f, 2.5f, 0.0f);
    drawPortal1frame->transform = new TransformComponent (Portal1frame.m_position , 3.5f, 5.5f, 0.05f);
//    drawPortal1frame->transform->setRotate(glm::vec3(0.f, 1.f, 0.f), -1.5708, glm::vec3(0.f, 1.f, 0.f), 0);
    Portal1frame.addComponent(drawPortal1frame->transform, "TransformComponent");
    Portal1frame.addComponent(drawPortal1frame, "DrawableComponent");


    //adding collision component
    collidePortal1frame = new CollisionComponent (Portal1frame.m_position, 3.f - (drawCylinder->transform->m_size/2.f), 5.f, 0.05f, "cube", false, m_camera, "port");
    Portal1frame.addComponent(collidePortal1frame, "CollisionComponent");


    drawPortal1 = new DrawableComponent (":/images/Barrel_texture.png", "portal1", "cube", true);  // <-------------------
    Portal1.m_position = glm::vec3(6.f, 2.5f, 0.1f);
    drawPortal1->transform = new TransformComponent (Portal1.m_position , 3.f, 5.f, 0.05f);
    Portal1.addComponent(drawPortal1->transform, "TransformComponent");
    Portal1.addComponent(drawPortal1, "DrawableComponent");
    Portal1.portal_forward = glm::vec3(0.f, 0.f, 1.f);
    Portal1.portal_up = glm::vec3(0.f, 1.f, 0.f);
    Portal1.portal_right = glm::vec3(-1.f, 0.f, 0.f);


    //adding collision component
    collidePortal1 = new CollisionComponent (Portal1.m_position, 3.f - (drawCylinder->transform->m_size/2.f), 5.f, 0.05f, "cube", false, m_camera, "port");
    Portal1.addComponent(collidePortal1, "CollisionComponent");


    //frame of 2
    drawPortal2frame = new DrawableComponent (":/images/COLORED_2.jpg", "portal2frame", "cube", false);
    Portal2frame.m_position = glm::vec3(0.01f, 2.5f, 10.f);
    drawPortal2frame->transform = new TransformComponent (Portal2frame.m_position , 3.5f, 5.5f, 0.05f);
    drawPortal2frame->transform->setRotate(glm::vec3(0.f, 1.f, 0.f), -1.5708, glm::vec3(0.f, 1.f, 0.f), 0);
    Portal2frame.addComponent(drawPortal2frame->transform, "TransformComponent");
    Portal2frame.addComponent(drawPortal2frame, "DrawableComponent");


    //adding collision component
    collidePortal2frame = new CollisionComponent (Portal2frame.m_position, 3.f - (drawCylinder->transform->m_size/2.f), 5.f, 0.05f, "cube", false, m_camera, "port");
    Portal2frame.addComponent(collidePortal2frame, "CollisionComponent");


    drawPortal2 = new DrawableComponent (":/images/Barrel_texture.png", "portal2", "quad", true);    // <-------------------
    Portal2.m_position = glm::vec3(0.05f, 2.5f, 10.f);
    Portal2.portal_forward = glm::vec3(1.f, 0.f, 0.f);
    Portal2.portal_up = glm::vec3(0.f, 1.f, 0.f);
    Portal2.portal_right = glm::vec3(0.f, 0.f, 1.f);
    drawPortal2->transform = new TransformComponent (Portal2.m_position , 3.f, 1.f, 5.f);
    //drawPortal2->transform = new TransformComponent (Portal2.m_position , 1.f, 1.f, 1.f);
    drawPortal2->transform->setRotate(glm::vec3(0.f, 0.f, 1.f), -1.5708, glm::vec3(0.f, 1.f, 0.f), 1.5708);
    Portal2.addComponent(drawPortal2->transform, "TransformComponent");
    Portal2.addComponent(drawPortal2, "DrawableComponent");


    //adding collision component
    collidePortal2 = new CollisionComponent (Portal2.m_position, 0.05f, 5.f, 3.f - (drawCylinder->transform->m_size/2.f), "cube", false, m_camera, "port");
    Portal2.addComponent(collidePortal2, "CollisionComponent");

    //Portal Objects end\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\



    //adding objs to drawable list of objs
    m_draw.addObj("cylinder", cylinder);
    m_draw.addObj("cube", Portal1);
    m_draw.addObj("cube2", Portal2);
    m_draw.addObj("portal2frame", Portal2frame);
    m_draw.addObj("portal1frame", Portal1frame);


    //m_pathfinder.addObj("cylinder2", cylinderEnemy);

    m_collide.addObj("portal1", Portal1);
    m_collide.addObj("portal2", Portal2);
    m_collide.addObj("portal2frame", Portal2frame);
    m_collide.addObj("portal1frame", Portal1frame);
    m_collide.addObj("cylinder", cylinder);
    m_collide.addObj("camera", camera);


    drawCylinderShadow->addMaterial(g);
    drawCylinder->addMaterial(g);
    drawPortal1->addMaterial(g);
    drawPortal2->addMaterial(g);
    drawPortal2frame->addMaterial(g);
    drawPortal1frame->addMaterial(g);
    drawCylinderPlayer->addMaterial(g);





    //assureChunks(g);
    drawSimple(g);
    //m_pathfinder.setRooms(curr.rooms);

    ui.setup(m_camera, g);

    //bells.fileName() = (":/sounds/music.png");


//    musicPlayer = new QMediaPlayer();
//    musicPlayer->setMedia(QUrl("qrc:/sounds/music2.wav"));
//    musicPlayer->setMedia(QUrl("http://www.maximumdonline.com/themes/pyramid.wav"));
//    musicPlayer->play();
    
//    soundPlayer = new QMediaPlayer();
//    soundPlayer->setMedia(QUrl("http://www.wavsource.com/snds_2020-03-30_7102365145747638/sfx/boing_x.wav"));

//    buzzer = new QMediaPlayer();
//    buzzer->setMedia(QUrl("http://www.wavsource.com/snds_2020-03-30_7102365145747638/sfx/chime.wav"));


    drawCylinderPlayer->transform->m_loc = glm::vec3(m_camera->m_pos.x, m_camera->m_pos.y - 2.5f, m_camera->m_pos.z);
    m_draw.addObj("cylinder3", camera);




    

}




//unimplemented, portals will bug out if resized as they rely on screen space coords
void GameWorld::resize(Graphics* g, int w, int h)
{

}



void GameWorld::assureChunks(Graphics* g)
{

    if(camera.m_position.x < currC_Pos.x )
    {
        once = true;
        currC_Pos = cEast.m_position;
        cWest = curr;
        curr = cEast;
        //m_pathfinder.setRooms(curr.rooms);

    }
    else if(camera.m_position.x > currC_Pos.x + offset)
    {
        once = true;
        currC_Pos = cWest.m_position;
        cEast = curr;
        curr = cWest;
        //m_pathfinder.setRooms(curr.rooms);

    }
    else if(camera.m_position.z < currC_Pos.z )
    {
        once = true;
        currC_Pos = cNorth.m_position;
        cSouth = curr;
        curr = cNorth;
        //m_pathfinder.setRooms(curr.rooms);

    }
    else if(camera.m_position.z > currC_Pos.z + offset)
    {
        once = true;
        currC_Pos = cSouth.m_position;
        cNorth = curr;
        curr = cSouth;
        //m_pathfinder.setRooms(curr.rooms);

    }
    else if(once) //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        once = false;
        //chunk #1 CURR ///////////////////////////////////////////////////////////
        int seed1 = rand();
        curr.makeChunk(0, 0, seed1);


        const std::shared_ptr<Shape> cu = curr.makeShape(true);
        cu->mo = "Chunk";

        g->addShape("Chunk", cu);

        c2 = new DrawableComponent (":/images/stoneNew.png", "stoneNew", "Chunk", false, rep);
        curr.m_position = currC_Pos;

        c2->transform = new TransformComponent (curr.m_position , 1.f);
        curr.addComponent(c2->transform, "TransformComponent");
        curr.addComponent(c2, "DrawableComponent");

        //adding collision component

        collideC = new CollisionComponent (curr.nW, curr.m_walls, m_camera, true);
        collideC->transformC(curr.m_position.x, curr.m_position.z);
        curr.nW = 0;
        curr.addComponent(collideC, "CollisionComponent");
        m_collide.addObj("curr", curr);


        m_objects["Chunk"] = curr;
        curr.name = "Chunk";
        m_draw.addObj("Chunk", curr);




        //chunk #2 NORTH //////////////////////////////////////////////////////////
        int seed2 = rand();
        cNorth.makeChunk(0, 0, seed2);


        const std::shared_ptr<Shape> c2u = cNorth.makeShape(true);
        g->addShape("Chunk2", c2u);

        cc2 = new DrawableComponent (":/images/stoneNew.png", "stoneNew", "Chunk2", false, rep);
        cNorth.m_position = glm::vec3(currC_Pos.x, currC_Pos.y, currC_Pos.z - offset);

        cc2->transform = new TransformComponent (cNorth.m_position , 1.f);
        cNorth.addComponent(cc2->transform, "TransformComponent");
        cNorth.addComponent(cc2, "DrawableComponent");

        m_objects["Chunk2"] = cNorth;
        cNorth.name = "Chun2k";
        m_draw.addObj("Chunk2", cNorth);


        //chunk #3 SOUTH /////////////////////////////////////////////////////////
        int seed3 = rand();
        cSouth.makeChunk(0, 0, seed3);


        const std::shared_ptr<Shape> c3u = cSouth.makeShape(true);
        g->addShape("Chunk3", c3u);

        ccc2 = new DrawableComponent (":/images/stoneNew.png", "stoneNew", "Chunk3", false, rep);
        cSouth.m_position = glm::vec3(currC_Pos.x, currC_Pos.y, currC_Pos.z + offset);

        ccc2->transform = new TransformComponent (cSouth.m_position , 1.f);
        cSouth.addComponent(ccc2->transform, "TransformComponent");
        cSouth.addComponent(ccc2, "DrawableComponent");


        m_objects["Chunk3"] = cSouth;
        cSouth.name = "Chunk3";
        m_draw.addObj("Chunk3", cSouth);


        //chunk #4 EAST /////////////////////////////////////////////////////////
        int seed4 = rand();
        cEast.makeChunk(0, 0, seed4);


        const std::shared_ptr<Shape> c4u = cEast.makeShape(true);
        g->addShape("Chunk4", c4u);

        cccc2 = new DrawableComponent (":/images/stoneNew.png", "stoneNew", "Chunk4", false, rep);
        cEast.m_position = glm::vec3(currC_Pos.x - offset, currC_Pos.y, currC_Pos.z);

        cccc2->transform = new TransformComponent (cEast.m_position , 1.f);
        cEast.addComponent(cccc2->transform, "TransformComponent");
        cEast.addComponent(cccc2, "DrawableComponent");


        m_objects["Chunk4"] = cEast;
        cEast.name = "Chunk4";
        m_draw.addObj("Chunk4", cEast);


        //chunk #5 WEST /////////////////////////////////////////////////////////
        int seed5 = rand();
        cWest.makeChunk(0, 0, seed5);


        const std::shared_ptr<Shape> c5u = cWest.makeShape(true);
        g->addShape("Chunk5", c5u);

        ccccc2 = new DrawableComponent (":/images/stoneNew.png", "stoneNew", "Chunk5", false, rep);
        cWest.m_position = glm::vec3(currC_Pos.x + offset, currC_Pos.y, currC_Pos.z);

        ccccc2->transform = new TransformComponent (cWest.m_position , 1.f);
        cWest.addComponent(ccccc2->transform, "TransformComponent");
        cWest.addComponent(ccccc2, "DrawableComponent");


        m_objects["Chunk5"] = cWest;
        cWest.name = "Chunk5";
        m_draw.addObj("Chunk5", cWest);
    }
}



void GameWorld::drawSimple(Graphics* g)
{
    //curr.makeChunk(0, 0, 0);
    curr.rooms[0][0].walls[0] = 1;
    curr.rooms[0][0].walls[1] = 1;
    curr.rooms[0][0].walls[2] = 1;
    curr.rooms[0][0].walls[3] = 1;



    const std::shared_ptr<Shape> cu = curr.makeShape(false);
    cu->mo = "Chunk";

    g->addShape("Chunk", cu);



    c2 = new DrawableComponent (":/images/stoneNew.png", "stoneNew", "Chunk", false, rep);
    c2->m_repeat = glm::vec2(10.f, 10.f);
    curr.m_position = currC_Pos;

    c2->transform = new TransformComponent (curr.m_position , 1.f);
    curr.addComponent(c2->transform, "TransformComponent");
    curr.addComponent(c2, "DrawableComponent");

    //adding collision component

    collideC = new CollisionComponent (curr.nW, curr.m_walls, m_camera, true);
    collideC->transformC(curr.m_position.x, curr.m_position.z);
    curr.nW = 0;
    curr.addComponent(collideC, "CollisionComponent");
    m_collide.addObj("curr", curr);


    m_objects["Chunk"] = curr;
    curr.name = "Chunk";
    m_draw.addObj("Chunk", curr);




    const std::shared_ptr<Shape> floor = curr.makeShape(true);
    floor->mo = "ChunkFloor";

    g->addShape("ChunkFloor", floor);


    f2 = new DrawableComponent (":/images/stoneNew.png", "stoneFloor", "ChunkFloor", false, rep);
    f2->m_repeat = glm::vec2(1.f, 1.f);
    curr.m_position = currC_Pos;

    f2->transform = new TransformComponent (curr.m_position , 1.f);
    curr.addComponent(f2->transform, "TransformComponent");
    curr.addComponent(f2, "DrawableComponent");

    //adding collision component

    collidef = new CollisionComponent (curr.nW, curr.m_walls, m_camera, true);
    collidef->transformC(curr.m_position.x, curr.m_position.z);
    curr.nW = 0;
    curr.addComponent(collidef, "CollisionComponent");
    m_collide.addObj("currF", curr);


    m_objects["ChunkFloor"] = curr;
    curr.name = "ChunkFloor";
    m_draw.addObj("ChunkFloor", curr);
}



void GameWorld::music_and_sound(float seconds)
{
    int length = 30;


        sec += seconds;



    if(sec != repeat)
    {
        repeat = (int)sec % length;
    }

    if(sec - follow > 0.1 && repeat >= length - 6)
    {
        vol -= 2;
        musicPlayer->setVolume(vol);
        follow = sec;
    }

    if(vol == 0)
    {
        musicPlayer->stop();
        musicPlayer->play();
    }

    if(sec - follow > 0.1  && repeat <= 5)
    {
        vol += 2;
        musicPlayer->setVolume(vol);
        follow = sec;
    }

    if(repeat > 5 && repeat < length - 6)
    {
        vol = 100;
    }
}


void GameWorld::checkTeleport()
{

    //The player character
    if(m_isThirdPerson)
    {

        if(drawCylinderPlayer->transform->m_loc.z < Portal1.m_position.z)
        {
            m_camera->m_pos = Portal2.m_position;
            pc.pos = Portal2.m_position;
            drawCylinderPlayer->transform->m_loc = Portal2.m_position;
            camera.m_position = Portal2.m_position;
            collideCam->fp(drawCylinderPlayer->transform->m_loc);
            m_camera->setLook(glm::normalize(glm::vec3(-m_camera->getLook().z, m_camera->getLook().y, m_camera->getLook().x)));
//            buzzer->stop();
//            buzzer->play();
        }
        else if(drawCylinderPlayer->transform->m_loc.x < Portal2.m_position.x)
        {
            m_camera->m_pos = Portal1.m_position;
            pc.pos = Portal1.m_position;
            drawCylinderPlayer->transform->m_loc = Portal1.m_position;
            camera.m_position = Portal1.m_position;
            collideCam->fp(drawCylinderPlayer->transform->m_loc);
            m_camera->setLook(glm::normalize(glm::vec3(m_camera->getLook().z, m_camera->getLook().y, -m_camera->getLook().x)));
//            buzzer->stop();
//            buzzer->play();
        }
    }
    else
    {
        if(m_camera->m_pos.z < Portal1.m_position.z)
        {
            glm::vec3 op = Portal2.m_position;
            m_camera->m_pos = op;
            camera.m_position = m_camera->getEye();
            collideCam->fp(camera.m_position);
            m_camera->setLook(glm::normalize(glm::vec3(-m_camera->getLook().z, m_camera->getLook().y, m_camera->getLook().x)));
//            buzzer->stop();
//            buzzer->play();
        }
        else if(m_camera->m_pos.x < Portal2.m_position.x)
        {
            glm::vec3 op = Portal1.m_position;
            m_camera->m_pos = op;
            camera.m_position = m_camera->getEye();
            collideCam->fp(camera.m_position);
            m_camera->setLook(glm::normalize(glm::vec3(m_camera->getLook().z, m_camera->getLook().y, -m_camera->getLook().x)));
//            buzzer->stop();
//            buzzer->play();
        }
    }




    //The non-player cube
    if(drawCylinder->transform->m_loc.z <= Portal1.m_position.z)
    {
        glm::vec3 op = glm::vec3(Portal2.m_position.x + 1.f, 0.f, Portal2.m_position.z);
        cylinder.m_position = op;
        drawCylinder->transform->m_loc = op;
        collideCylinder->circlePos = op;
//        buzzer->stop();
//        buzzer->play();
    }
    else if(drawCylinder->transform->m_loc.x < Portal2.m_position.x)
    {
        glm::vec3 op = glm::vec3(Portal1.m_position.x, 0.f, Portal1.m_position.z + 1.f);
        cylinder.m_position = op;
        drawCylinder->transform->m_loc = op;
        collideCylinder->circlePos = op;
//        buzzer->stop();
//        buzzer->play();
    }




    //adding the shadow obj
//        if(drawCylinder->transform->m_loc.z - (drawCylinder->transform->m_size/2.f) < Portal1.m_position.z)
//        {

//            //glm::vec3 opv1 = Portal2.m_position + (drawCylinder->transform->m_loc.z - (drawCylinder->transform->m_size/2.f));
//            glm::vec3 opv1 = glm::vec3(Portal2.m_position.x + (drawCylinder->transform->m_loc.z - (drawCylinder->transform->m_size/2.f)), 0.f, Portal2.m_position.z);

//            drawCylinderShadow->transform->m_loc = opv1;
//            collideCylinderShadow->fp(opv1);





//            m_collide.addObj("cylinderShadow", cylinderShadow);
//            m_draw.addObj("cylinderShadow", cylinderShadow);

//            std::cout << "hit" << std::endl;
//           //std::cout << drawCylinder->transform->m_loc.x << ", " << drawCylinder->transform->m_loc.y << ", " << drawCylinder->transform->m_loc.z << std::endl;

//        }
//        else if (drawCylinder->transform->m_loc.x - (drawCylinder->transform->m_size/2.f) < Portal2.m_position.x)
//        {
//            glm::vec3 op = glm::vec3(Portal1.m_position.x, 0.f, Portal1.m_position.z);

//            drawCylinderShadow->transform->m_loc = op;
//            collideCylinderShadow->fp(op);
//            m_collide.addObj("cylinderShadow", cylinderShadow);
//            m_draw.addObj("cylinderShadow", cylinderShadow);

//        }


    //removing the shadow obj
//        if(drawCylinder->transform->m_loc.z + (drawCylinder->transform->m_size/2.f) > Portal1.m_position.z)
//        {
//            m_collide.remObj("cylinderShadow");
//            m_draw.remObj("cylinderShadow");
//        }
//        else if (drawCylinder->transform->m_loc.x + (drawCylinder->transform->m_size/2.f) > Portal2.m_position.x)
//        {
//            m_collide.remObj("cylinderShadow");
//            m_draw.remObj("cylinderShadow");
//        }


}


void GameWorld::tick(float seconds)
{


   // music_and_sound(seconds);
    sec += seconds;





    if(m_isThirdPerson)
    {
        collideCam->circleRad = 0.7333333f;
        m_camera->m_pos = glm::vec3(m_camera->m_pos.x, m_camera->m_pos.y - 2.5f, m_camera->m_pos.z);
        drawCylinderPlayer->transform->m_loc = m_camera->m_pos;
        //m_draw.addObj("cylinder3", camera);
        m_camera->setEye(m_camera->m_pos - (5.f * m_camera->getLook()));
        camera.m_position = m_camera->m_pos;

        collideCam->fp(drawCylinderPlayer->transform->m_loc);



    }
    else
    {
        drawCylinderPlayer->transform->m_loc = glm::vec3(m_camera->m_pos.x, m_camera->m_pos.y - 2.5f, m_camera->m_pos.z);
        collideCam->circleRad = 0.7333333f;
        //m_draw.remObj("cylinder3");
        camera.m_position = m_camera->getEye();

        collideCam->fp(camera.m_position);

        //std::cout << "First Person" << std::endl;
    }



    //m_pathfinder.onTick(sec, offset, cNorth.m_position, cSouth.m_position, cEast.m_position, cWest.m_position);


    cylinder.onTick(seconds);




    m_collide.onTick(&lose);

//    if(m_isThirdPerson)
//    {
//        m_camera->m_pos = glm::vec3(m_camera->m_pos.x, m_camera->m_pos.y + 2.5f, m_camera->m_pos.z);
//    }

      pc.onTick(m_camera, &m_isThirdPerson);


      checkTeleport();


}






void GameWorld::draw(Graphics* g)
{
    drawSimple(g);









    //rendering #1 with first cam FBO#1
    glUseProgram(m_portalProgram);

    //std::cout <<  g->sizeOfViewport.y << std::endl;
    glm::vec3 d = drawPortal1->transform->m_loc - m_camera->getEye();
    float theta = -glm::acos(glm::dot(Portal1.portal_forward, Portal2.portal_forward));
//    glm::mat4x4 rot = glm::mat4(glm::cos(theta), 0, glm::sin(theta), 0,
//                                0, 1, 0, 0,
//                                -glm::sin(theta), 0, glm::cos(theta), 0,
//                                0, 0, 0, 1);
    glm::mat4x4 rot = glm::rotate(glm::mat4(), theta, glm::vec3(0, 1, 0));


    glm::vec3 why = drawPortal2->transform->m_loc - glm::vec3(rot * glm::vec4(d, 1));
    m_camera1->m_pos = why;
    m_camera1->setEye(why);


    m_camera1->setLook(glm::vec3(rot * glm::vec4(m_camera->getLook(), 1)));
    //m_camera1->setLook( glm::vec3(1, 0, 0));






    g->setCamera(m_camera1);

    FBO* m_blurFBO1 = new FBO(g->sizeOfViewport.x, g->sizeOfViewport.y);

    m_draw.remObj("cube");
    m_draw.remObj("cube2");

    m_draw.remObj("portal1frame");
    m_draw.remObj("portal2frame");


    m_blurFBO1->bind();


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_draw.drawObjs(g);

    m_blurFBO1->unbind();




    //rendering #2 with second cam FBO#2



    glm::vec3 d2 = drawPortal2->transform->m_loc - m_camera->getEye();
    float theta2 = glm::acos(glm::dot(Portal2.portal_forward, Portal1.portal_forward));
//    glm::mat4x4 rot2 = glm::mat4(glm::cos(theta2), 0, glm::sin(theta2), 0,
//                                0, 1, 0, 0,
//                                -glm::sin(theta2), 0, glm::cos(theta2), 0,
//                                0, 0, 0, 1);
    glm::mat4x4 rot2 = glm::rotate(glm::mat4(), theta2, glm::vec3(0, 1, 0));


    glm::vec3 why2 = drawPortal1->transform->m_loc - glm::vec3(rot2 * glm::vec4(d2, 1));
    m_camera2->m_pos = why2;
    m_camera2->setEye(why2);


    m_camera2->setLook(glm::vec3(rot2 * glm::vec4(m_camera->getLook(), 1)));
    //m_camera1->setLook( glm::vec3(1, 0, 0));



    g->setCamera(m_camera2);

    FBO* m_blurFBO2 = new FBO(g->sizeOfViewport.x, g->sizeOfViewport.y);

    m_blurFBO2->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_draw.drawObjs(g);

    m_blurFBO2->unbind();




    //stuff
    glUseProgram(0);
    glUseProgram(m_normProgram);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_draw.addObj("cube", Portal1);
    m_draw.addObj("cube2", Portal2);

    //m_draw.addObj("portal1frame", Portal1frame);
   // m_draw.addObj("portal2frame", Portal2frame);



    drawPortal2->addMaterialPortal(m_blurFBO2);
    drawPortal1->addMaterialPortal(m_blurFBO1);



    //rendering #3 with final camera to screen

    g->setCamera(m_camera);

    if(!m_isThirdPerson)
        m_draw.remObj("cylinder3");

    m_draw.drawObjs(g);
    m_draw.addObj("cylinder3", camera);


    delete m_blurFBO1;
    delete m_blurFBO2;
    glUseProgram(0);

}

void GameWorld::onKeyPressed(QKeyEvent*event)
{

    if(event->key() == Qt::Key_V)
    {
        m_isThirdPerson = !m_isThirdPerson;
        //buzzer->stop();
        //buzzer->play();
    }
    else
    {
        if (event->key() == Qt::Key_Space)
        {
//                soundPlayer->stop();
//                soundPlayer->play();
        }

        pc.onKeyPress(event);
    }


}

void GameWorld::onMouseDragged(QMouseEvent* event, int dx, int dy)
{
    //m_camera->rotate(-dx / 1000.f, -dy / 1000.f);
    pc.onMouseDragged(event, dx, dy);
}

void GameWorld::keyRepeatEvent(QKeyEvent *event)
{



}


void GameWorld::keyReleaseEvent(QKeyEvent *event)
{
    pc.onKeyRelease(event);

}

void GameWorld::releaseKeys()
{
    pc.releaseKeys();




}

std::shared_ptr<Camera> GameWorld::getcam()
{
    return m_camera;
}




