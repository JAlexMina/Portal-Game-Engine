#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "systems.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Material.h"


class UISystem : public systems
{
public:
    UISystem();
    void setup(std::shared_ptr<Camera> camera, Graphics* g);
    glm::vec3 convertToScreenSpace(glm::vec3 pos, glm::vec2 screenSize);
    void draw2D(glm::vec3 pos);
    void addMaterial(Graphics* g, std::string name, glm::vec3 color);
    //Material m_material;

    std::shared_ptr<Camera> m_camera;
    Graphics* m_g;


};

#endif // UISYSTEM_H
