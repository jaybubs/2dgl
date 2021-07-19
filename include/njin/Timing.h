#pragma once
#include <SDL2/SDL.h>
namespace njin {
  class FPSLimiter
  {
  public:
    FPSLimiter ();
    ~FPSLimiter ();
    /* float targetFPS; */

    void init(float maxFPS);
    //time at the beginning of the frame
    void begin();
    //time at the end, return the actual fps
    float end();
  private:
    unsigned int startTicks;
    
    float fps;
    float frameTime;
    float maxfps;

    void calculateFPS();
  };

}
