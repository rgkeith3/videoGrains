#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
  playheadPos = 0.0;
  lastTrigger = ofGetElapsedTimef();
  blendMode = OF_BLENDMODE_ADD;
  blendModeFlipFlop = false;
  blendModeEnabled = true;

  sequence.loadSequence("output_", "png", 1, 251, 4);
  sequence.preloadAllFrames();
  sequence.setFrameRate(30);
  ofBackground(0, 0, 0);

  blendModeSlider.addListener(this, &ofApp::blendModeChanged);

  gui.setup();
  gui.add(grainTriggerCps.setup("grain trigger period", 1, 0.01, 2));
  gui.add(triggerVariance.setup("trigger variance", 0, 0, 1));
  gui.add(playheadSpeed.setup("playhead speed", 1, -2, 2));
  gui.add(grainStartVariance.setup("grain start variance", 0, 0, 1));
  gui.add(grainSize.setup("grain size", 0.1, 0.001, 1.0));
  gui.add(grainSizeVariance.setup("grain size variance", 0, 0, 1));
  gui.add(grainSpeed.setup("grain speed", 1, 0.1, 4.0));
  gui.add(grainSpeedVariance.setup("grain speed variance", 0, 0, 1));
  gui.add(blendModeSlider.setup("grain blend mode", 0, 0, 5));
  gui.add(blendModeLabel.setup("blend mode", "add"));
}

void ofApp::exit()
{
  blendModeSlider.removeListener(this, &ofApp::blendModeChanged);
}

//--------------------------------------------------------------
void ofApp::update()
{
  for (int i = 0; i < grains.size(); i++)
  {
    if (!grains[i].update())
    {
      grains.erase(grains.begin() + i);
    }
  }

  ofApp::advancePlayhead();

  float now = ofGetElapsedTimef() + ofRandom((triggerVariance * -1 * grainTriggerCps), triggerVariance * grainTriggerCps);
  if ((lastTrigger + grainTriggerCps) < now)
  {
    lastTrigger = now;
    ofApp::addGrain();
  }
}

//--------------------------------------------------------------
void ofApp::draw()
{
  for (int i = 0; i < grains.size(); i++)
  {
    if (i == 0)
    {
      ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    }

    if (blendModeEnabled)
    {
      if (blendModeFlipFlop)
      {
        if (i % 2 == 0)
        {
          ofEnableBlendMode(OF_BLENDMODE_ADD);
        }
        else
        {
          ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
        }
      }
      else
      {
        ofEnableBlendMode(blendMode);
      }
    }
    float pos = grains[i].getPos();
    sequence.getTextureForPercent(pos).draw(0, 0);
  }

  gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

void ofApp::addGrain()
{
  float startPos = playheadPos + ofRandom((grainStartVariance * -1), grainStartVariance);
  float tempSize = grainSize + ofRandom((grainSizeVariance * -1), grainSizeVariance);
  float tempSpeed = grainSpeed + ofRandom((grainSpeedVariance * -1), grainSpeedVariance);
  VideoGrain tempGrain;
  tempGrain.setup(startPos, tempSpeed, tempSize);
  grains.push_back(tempGrain);
}

void ofApp::advancePlayhead()
{
  // once again i'm too lazy to do math so this is a crude playhead speed ticker
  playheadPos += (0.01 * playheadSpeed);
  if (playheadPos >= 1)
  {
    playheadPos = playheadPos - 1;
  }
  else if (playheadPos < 0)
  {
    playheadPos = playheadPos + 1;
  }
}

void ofApp::blendModeChanged(int &blendModeSlider)
{
  blendModeFlipFlop = false;
  blendModeEnabled = true;
  if (blendModeSlider == 0)
  {
    blendMode = OF_BLENDMODE_ADD;
    blendModeLabel = "add";
  }
  else if (blendModeSlider == 1)
  {
    blendMode = OF_BLENDMODE_SUBTRACT;
    blendModeLabel = "subtract";
  }
  else if (blendModeSlider == 2)
  {
    blendMode = OF_BLENDMODE_MULTIPLY;
    blendModeLabel = "multiply";
  }
  else if (blendModeSlider == 3)
  {
    blendMode = OF_BLENDMODE_SCREEN;
    blendModeLabel = "screen";
  }
  else if (blendModeSlider == 4)
  {
    blendModeFlipFlop = true;
    blendModeLabel = "flip flop";
  }
  else
  {
    blendModeEnabled = false;
    blendModeLabel = "DISABLED";
  }
}