#pragma once

#include "ofMain.h"
#include "ofxImageSequence.h"
#include "ofxGui.h"
#include "VideoGrain.h"

class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void addGrain();
	void advancePlayhead();
	string blendModeString();
	void blendModeChanged(int &blendModeSlider);

	float lastTrigger;
	float playheadPos;

	ofBlendMode blendMode;
	bool blendModeFlipFlop;
	bool blendModeEnabled;

	ofxImageSequence sequence;

	vector<VideoGrain> grains;

	ofxPanel gui;
	ofxFloatSlider grainTriggerCps;
	ofxFloatSlider triggerVariance;
	ofxFloatSlider playheadSpeed;
	ofxFloatSlider grainStartVariance;
	ofxFloatSlider grainSize;
	ofxFloatSlider grainSizeVariance;
	ofxFloatSlider grainSpeed;
	ofxFloatSlider grainSpeedVariance;
	ofxIntSlider blendModeSlider;
	ofxLabel blendModeLabel;
};
