#pragma once


#include "ofMain.h"


#include "ofxMidi.h"


class midiInput :  public ofxMidiListener{
    
public:
    midiInput();
    
    void exit();
    void newMidiMessage(ofxMidiMessage& eventArgs);
    void showMidi();
    int channels();
  
    
	ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;
    
    stringstream text;
    int maxMidi;
    int roll;
    int tiltCam;
    int moveCam;
    int channelValue;
    float setZ;
    float setScaleZ;
    int  swMode;
    bool bChangeColor;
    float prevDelta;
};