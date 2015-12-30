#include "MainGame.h"
#include "MainWorld.h"

MainGame::MainGame() : Game(800, 600, 0, "GameEngine")
{
    setBackgroundColor(BadEngine::Color(0, 45, 75, 0));
    printf(" *** OpenGL version: %s *** \n You need at least version %5.2f to run the game. \n", 
           reinterpret_cast<const char*>(glGetString(GL_VERSION)), m_OpenGLVersion);
    loadWorld<MainWorld>();
}
