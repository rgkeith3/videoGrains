#include "VideoGrain.h"
VideoGrain::VideoGrain()
{
}

void VideoGrain::setup(float _startPos, float _speed, float _size)
{
  position = _startPos;
  speed = _speed;
  // this is incorrect size calculation
  endPos = _startPos + _size;
}

bool VideoGrain::update()
{
  if (position < endPos && position < 1.0)
  {
    // TODO: this is a crude playback speed thing. fix this so that speed 1 plays back at actual framerate or default 30
    position += (0.01 * speed);
    return true;
  }
  else
  {
    return false;
  }
}

float VideoGrain::getPos()
{
  return position;
}