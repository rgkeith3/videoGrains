#ifndef _VIDEO_GRAIN

#define _VIDEO_GRAIN

#include "ofMain.h"

class VideoGrain
{
public:
  void setup(float _startPos, float _speed, float _size);
  bool update();
  float getPos();

  float position;
  float speed;
  float endPos;

  VideoGrain();
};

#endif