#include "Timing.h"

namespace njin {
  FPSLimiter::FPSLimiter(){

  }

  FPSLimiter::~FPSLimiter(){

  }
  
  void FPSLimiter::init(float maxFPS) {
    maxfps = maxFPS;
  }

  void FPSLimiter::begin() {
    startTicks = SDL_GetTicks();

  }
  float FPSLimiter::end() {
    calculateFPS();

    float frameTicks = SDL_GetTicks() - startTicks;
    //fps limiter
    if (1000.0f / maxfps > frameTicks) {
      SDL_Delay(1000.0f / maxfps - frameTicks);
    }
    return fps;
  }

  void FPSLimiter::calculateFPS() {
    static const int NUM_SAMPLES = 10; //static - init only once
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static float prevTicks = SDL_GetTicks();
    float currentTicks;
    currentTicks = SDL_GetTicks();

    frameTime = currentTicks - prevTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = frameTime;

    prevTicks = currentTicks;

    int count;

    currentFrame++;

    if (currentFrame < NUM_SAMPLES) {
      count = currentFrame;
    } else {
      count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++) {
      frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;

    if (frameTimeAverage > 0) {
      fps = 1000.0f / frameTimeAverage;
    } else {
      fps = 60.0f; // protect against div / 0
    }


  }
}
