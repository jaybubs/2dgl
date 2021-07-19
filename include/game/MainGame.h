#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <njin/Sprite.h>
#include <njin/GLSLProgram.h>
#include <njin/GLTexture.h>
#include <njin/Window.h>
#include <vector>
#include <njin/Njin.h>
#include <njin/Camera2D.h>
#include <njin/SpriteBatch.h>
#include <njin/InputManager.h>
#include <njin/Timing.h>

enum class GameState {
  PLAY,
  EXIT
};

/* modules are instantiated here */
class MainGame
{
private:
  njin::Window gameWindow;
  int screenWidth;
  int screenHeight;
  GameState gameState;

  njin::GLSLProgram colorProg;
  njin::Camera2D camera;
  njin::SpriteBatch spriteBatch;
  njin::InputManager inputManager;
  njin::FPSLimiter fpsLimiter;



  float time;
  njin::GLTexture playerTexture;

  float maxfps;
  float fps;
  
  void initSystems();
  void processInput();
  void gameLoop();
  void drawGame();
  void initShaders();

public:
  MainGame();
  ~MainGame();

  void run();

};
