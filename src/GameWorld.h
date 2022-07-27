#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <map>

#include "GameObject.h"
#include "systems.h"
#include <engine/graphics/Graphics.h>
#include "engine/util/CommonIncludes.h"
#include <QGLWidget>
#include <QTime>
#include <QTimer>
#include <memory>
#include <engine/graphics/Graphics.h>
#include <engine/graphics/Camera.h>
#include "screen.h"
#include "GameObject.h"
#include "drawablecomponent.h"
#include "DrawSystem.h"
#include "PlayerControlComponent.h"
#include "CollisionSystem.h"
#include "CollisionComponent.h"
#include "EnemyResponseComponent.h"
#include "Chunk.h"
#include "PathFinderSystem.h"
#include "PathFinderComponent.h"
#include "UISystem.h"
#include <QMediaPlayer>
#include <QSound>


class GameWorld : public screen
{
public:
    GameWorld();

    //void onTick(float seconds);
    //void onDraw(Graphics *g);

    glm::vec2 rep = glm::vec2(1, 1);


    void tick(float seconds);
    void draw(Graphics* g);
    void onKeyPressed(QKeyEvent*event);
    // more device and event types here...
    void onMouseDragged(QMouseEvent*event, int dx, int dy);
    void setup(Graphics* g);
    void resize(Graphics* g, int w, int h);
    void keyRepeatEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void releaseKeys();
    void assureChunks(Graphics* g);

    std::shared_ptr<Camera> getcam();
    PlayerControlComponent pc;
    float sec;
    bool once = true;


    //creating objs
    GameObject cylinderEnemy;

    GameObject Portal1;
    GameObject Portal2;
    GameObject Portal1frame;
    GameObject Portal2frame;
    GameObject floor;
    GameObject camera;


    GameObject cylinder;
    GameObject cylinderShadow;


    CollisionComponent* collideCylinder;
    CollisionComponent* collideCylinderShadow;

    CollisionComponent* collideCylinderEnemy;
    CollisionComponent* collidePortal1;
    CollisionComponent* collidePortal2;
    CollisionComponent* collidePortal1frame;
    CollisionComponent* collidePortal2frame;
    CollisionComponent* collideCam;
    CollisionComponent* collideN;
    CollisionComponent* collideS;
    CollisionComponent* collideE;
    CollisionComponent* collideW;
    CollisionComponent* collideC;
    CollisionComponent* collidef;


    PathFinderComponent* CylinderEnemyAI;
    DrawableComponent* drawCylinderEnemy;
    DrawableComponent* drawCylinderPlayer;
    DrawableComponent* drawCylinder;
    DrawableComponent* drawCylinderShadow;
    DrawableComponent* drawPortal1;
    DrawableComponent* drawPortal2;
    DrawableComponent* drawPortal1frame;
    DrawableComponent* drawPortal2frame;

    DrawableComponent* c2;
    DrawableComponent* f2;
    DrawableComponent* cc2;
    DrawableComponent* ccc2;
    DrawableComponent* cccc2;
    DrawableComponent* ccccc2;



    float offset = 90.f;
    int repeat = 0;
    QMediaPlayer *musicPlayer;
    QMediaPlayer *soundPlayer;
    QMediaPlayer *buzzer;
    int vol = 0;
    float follow = 0;


    bool m_isThirdPerson;

    bool lose;
    bool win;

    Chunk cNorth;
    Chunk cSouth;
    Chunk cEast;
    Chunk cWest;

    Chunk curr;

    glm::vec3 currC_Pos = glm::vec3(0.f, 0.f, 0.f);

    void music_and_sound(float seconds);

    void checkTeleport();


    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Camera> m_camera1;
    std::shared_ptr<Camera> m_camera2;


    void drawSimple(Graphics* g);
    int f = 10;


    //std::shared_ptr<FBO> m_blurFBO1;// (new FBO(g->sizeOfViewport.x, g->sizeOfViewport.y));;




private:
    std::map<std::string, GameObject> m_objects;
    std::map<std::string, systems> m_systems;
    DrawSystem m_draw;
    CollisionSystem m_collide;
    PathFinderSystem m_pathfinder;
    UISystem ui;

    GLuint m_normProgram;
    GLuint m_portalProgram;

    //QSound bells;
};

#endif // GAMEWORLD_H
