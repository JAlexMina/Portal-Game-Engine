QT += core gui opengl multimedia



TARGET = cs195u_engine
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

unix:!macx {
    LIBS += -lGLU
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
    CONFIG += c++11
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32
}

SOURCES += \
    libs/glew-1.10.0/src/glew.c \
    src/UISystem.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/view.cpp \
    src/viewformat.cpp \
    src/engine/graphics/ResourceLoader.cpp \
    src/engine/graphics/FBO.cpp \
    src/engine/graphics/IBO.cpp \
    src/engine/graphics/Texture.cpp \
    src/engine/graphics/Texture1D.cpp \
    src/engine/graphics/Texture2D.cpp \
    src/engine/graphics/Texture3D.cpp \
    src/engine/graphics/VAO.cpp \
    src/engine/graphics/VBO.cpp \
    src/engine/graphics/VBOAttribMarker.cpp \
    src/engine/graphics/Font.cpp \
    src/engine/graphics/DepthBuffer.cpp \
    src/engine/graphics/RenderBuffer.cpp \
    src/engine/graphics/GraphicsDebug.cpp \
    src/engine/graphics/Shader.cpp \
    src/engine/graphics/Camera.cpp \
    src/engine/graphics/Shape.cpp \
    src/engine/graphics/Graphics.cpp \
    src/engine/graphics/Material.cpp \
    src/engine/graphics/Light.cpp \
    src/application.cpp \
    src/CollisionComponent.cpp \
    src/CollisionSystem.cpp \
    src/Component.cpp \
    src/drawablecomponent.cpp \
    src/DrawSystem.cpp \
    src/EnemyResponseComponent.cpp \
    src/GameObject.cpp \
    src/GameWorld.cpp \
    src/screen.cpp \
    src/PlayerControlComponent.cpp \
    src/systems.cpp \
    src/TickSystem.cpp \
    src/TransformComponent.cpp \
    src/warmupscreen1.cpp \
    src/warmupscreen2.cpp \
    src/warmupscreen3.cpp \
    src/Chunk.cpp \
    src/Room.cpp \
    src/PathFinderSystem.cpp \
    src/PathFinderComponent.cpp \
    src/BehaviorTreeNode.cpp \
    src/Wander.cpp

HEADERS += \
    libs/glew-1.10.0/include/GL/glew.h \
    libs/stb/stb_rect_pack.h \
    libs/stb/stb_truetype.h \
    src/UISystem.h \
    src/mainwindow.h \
    src/view.h \
    src/viewformat.h \
    src/engine/util/CommonIncludes.h \
    src/engine/graphics/ResourceLoader.h \
    src/engine/graphics/CylinderData.h \
    src/engine/graphics/SphereData.h \
    src/engine/graphics/FBO.h \
    src/engine/graphics/IBO.h \
    src/engine/graphics/Texture.h \
    src/engine/graphics/Texture1D.h \
    src/engine/graphics/Texture2D.h \
    src/engine/graphics/Texture3D.h \
    src/engine/graphics/VAO.h \
    src/engine/graphics/VBO.h \
    src/engine/graphics/VBOAttribMarker.h \
    src/engine/graphics/CubeData.h \
    src/engine/graphics/Font.h \
    src/engine/graphics/DepthBuffer.h \
    src/engine/graphics/RenderBuffer.h \
    src/engine/graphics/GraphicsDebug.h \
    src/engine/graphics/Shader.h \
    src/engine/graphics/ShaderAttribLocations.h \
    src/engine/graphics/Camera.h \
    src/engine/graphics/Graphics.h \
    src/engine/graphics/Shape.h \
    src/engine/graphics/Material.h \
    src/engine/graphics/Light.h \
    src/engine/graphics/Constants.h \
    src/application.h \
    src/CollisionComponent.h \
    src/CollisionSystem.h \
    src/Component.h \
    src/drawablecomponent.h \
    src/DrawSystem.h \
    src/EnemyResponseComponent.h \
    src/GameObject.h \
    src/GameWorld.h \
    src/screen.h \
    src/PlayerControlComponent.h \
    src/systems.h \
    src/TickSystem.h \
    src/TransformComponent.h \
    src/warmupscreen1.h \
    src/warmupscreen2.h \
    src/warmupscreen3.h \
    src/Chunk.h \
    src/Room.h \
    src/PathFinderSystem.h \
    src/PathFinderComponent.h \
    src/BehaviorTreeNode.h \
    src/Wander.h

FORMS += src/mainwindow.ui

RESOURCES += \
    res/OBJs/OBJs.qrc \
    res/shaders/shaders.qrc \
    res/fonts/fonts.qrc \
    res/images/images.qrc

OTHER_FILES += \
    res/images/grass.png \
    res/images/no-Image.png

DISTFILES += \
    res/OBJs/Koltuk.obj \
    res/OBJs/seahorse.obj \
    res/images/COLORED_2.jpg \
    res/images/CORRED_1.jpg \
    res/images/marble.png \
    res/images/newStone.png \
    res/images/marble.png \
    res/images/stone2.png \
    res/images/terrain.png \
    res/shaders/shader.vert \
    res/shaders/shader.frag \
    res/images/Barrel_texture.png \
    res/images/grass_minecraft.png \
    res/images/sky.png \
    res/images/sky2.png \
    res/images/Sky3.png \
    res/images/stoneNew.png \
    res/OBJs/buddha.obj \
    res/OBJs/natkins.obj \
    res/OBJs/dragon.obj


INCLUDEPATH += src libs glm libs/glew-1.10.0/include
DEPENDPATH += src libs glm libs/glew-1.10.0/include

# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON += -Waddress -Warray-bounds -Wc++0x-compat -Wchar-subscripts -Wformat\
                          -Wmain -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type \
                          -Wsequence-point -Wsign-compare -Wstrict-overflow=1 -Wswitch \
                          -Wtrigraphs -Wuninitialized -Wunused-label -Wunused-variable \
                          -Wvolatile-register-var -Wno-extra

QMAKE_CXXFLAGS += -g
