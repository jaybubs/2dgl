#include "MainGame.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_video.h"
#include "glm/gtx/dual_quaternion.hpp"
#include "njin/GLTexture.h"
#include "njin/ResourceManager.h"
#include "njin/Vertex.h"
#include <njin/Errors.h>
#include <njin/ImageLoader.h>
#include <iostream>

MainGame::MainGame() : 
  screenWidth(1024),
  screenHeight(768),
  gameState(GameState::PLAY),
  time(0.0f),
  maxfps(60.0f)
{
  camera.init(screenWidth, screenHeight);
}

MainGame::~MainGame() {
  /* gameWindow = nullptr; */
}

void MainGame::run() {
  initSystems();

  
  gameLoop();
}

void MainGame::initSystems() {

  gameWindow.create("Game Engine", screenWidth, screenHeight, 0);

  initShaders();

  spriteBatch.init();
  fpsLimiter.init(maxfps);

}

void MainGame::gameLoop() {
  while (gameState != GameState::EXIT) {
    fpsLimiter.begin();

    processInput();
    time += 0.01;

    camera.update();

    //update all bullets
    for (uint i = 0; i < bullets.size();) {
      if (bullets[i].update() == true) {
        bullets[i] = bullets.back();
        bullets.pop_back();
      } else {
      i++;
      }
    }

    drawGame();

    fps = fpsLimiter.end();

    //print every 10 frames, for now just cout
    static int frameCounter = 0;
    frameCounter++;
    if (frameCounter == 1000) {
      std::cout << fps << std::endl;
      frameCounter = 0;
    }

  }
}

void MainGame::processInput() {
  SDL_Event e;

  const float CAM_SPEED = 10.0f;
  const float SCALE_SPEED = 0.1f;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        gameState = GameState::EXIT;
        break;
      case SDL_MOUSEMOTION:
        inputManager.setMouseCoords(e.motion.x, e.motion.y);
        break;
      case SDL_KEYDOWN:
        inputManager.pressKey(e.key.keysym.sym);
        break;
      case SDL_KEYUP:
        inputManager.releaseKey(e.key.keysym.sym);
        break;
      case SDL_MOUSEBUTTONDOWN:
        inputManager.pressKey(e.button.button);
        break;
      case SDL_MOUSEBUTTONUP:
        inputManager.releaseKey(e.button.button);
        break;

    }

  }
  if (inputManager.isKeyPressed(SDLK_COMMA)) {
    camera.setPosition(camera.getPosition() + glm::vec2(0.0, CAM_SPEED));
  }
  if (inputManager.isKeyPressed(SDLK_o)) {
    camera.setPosition(camera.getPosition() + glm::vec2(0.0, -CAM_SPEED));
  }
  if (inputManager.isKeyPressed(SDLK_a)) {
    camera.setPosition(camera.getPosition() + glm::vec2(-CAM_SPEED, 0.0));
  }
  if (inputManager.isKeyPressed(SDLK_e)) {
    camera.setPosition(camera.getPosition() + glm::vec2(CAM_SPEED, 0.0));
  }
  if (inputManager.isKeyPressed(SDLK_q)) {
    camera.setScale(camera.getScale() + SCALE_SPEED);
  }
  if (inputManager.isKeyPressed(SDLK_j)) {
    camera.setScale(camera.getScale() - SCALE_SPEED);
  }

  if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
    glm::vec2 mouseCoords = camera.convertSTW(inputManager.mouseCoords);

    glm::vec2 playerPosition(0.0f);
    glm::vec2 direction = mouseCoords - playerPosition;
    //turn dirxn into a unit vector
    direction = glm::normalize(direction);

    bullets.emplace_back(playerPosition, direction, 1.0f, 100);
    }
  
}

void MainGame::drawGame() {

  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  colorProg.use();

  // multitexturing, put as 0 for now
  glActiveTexture(GL_TEXTURE0);
  GLint textureLocation = colorProg.getUniformLocation("mySampler");
  //tell tex loc we're using it as texture 0
  glUniform1i(textureLocation, 0);

  //time can be passed into the fragment shader thru a unifrm set here
  /* GLint timeLocation = colorProg.getUniformLocation("time"); */
  /* glUniform1f(timeLocation, time); */

  //set the camera matrix
  GLint pLocation = colorProg.getUniformLocation("P");
  glm::mat4 cameraMatrix = camera.getCameraMatrix();

  glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

  spriteBatch.begin();
  //draw batches here
  //x,y,scalex,scaley
  glm::vec4 pos(0.0f, 0.0f, 150.0f, 150.0f);
  glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
  njin::GLTexture cock = njin::ResourceManager::getTexture("res/textures/majestickcock.png");
  njin::Color color;
  color.r = 255;
  color.g = 255;
  color.b = 255;
  color.a = 255;

  //loop through all existing bullets
  for (uint i = 0; i < bullets.size(); i++) {
    bullets[i].draw(spriteBatch);
  }
  
  spriteBatch.draw(pos, uv, cock.id, 0.0f, color);

  spriteBatch.end();

  spriteBatch.renderBatch();

  //unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);

  colorProg.unuse();

  //switch between the two buffers summoned in initsystems
  gameWindow.swapBuffer();
}

void MainGame::initShaders() {
  colorProg.createShaders("res/shaders/colorShading.vert", "res/shaders/colorShading.frag");
  colorProg.addAttr("vertexPosition");
  colorProg.addAttr("vertexColor");
  colorProg.addAttr("vertexUV");
  colorProg.linkShaders();
}

