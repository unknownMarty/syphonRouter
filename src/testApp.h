#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxUI.h"
#include "midiInput.h"

class testApp : public ofBaseApp{
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
    void exit();
	
	float 	counter;
	bool	bSmooth;
	
    ofTexture tex;
    
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonServer individualTextureSyphonServer;
	
	ofxSyphonClient mClient;
    ofxSyphonClient mClient2;
    ofxSyphonClient mClient3;
    
      void* latestImage;
    
    ofxUICanvas *gui2;
    
    ofTrueTypeFont font;
    
    void switchInput();
    int screen;
    
    	void setGUI2();
    
    void guiEvent(ofxUIEventArgs &e);
    string SYPHON1app;
    string SYPHON2app;
    string SYPHON3app;
    
    string SYPHON1syphon;
    string SYPHON2syphon;
    string SYPHON3syphon;
    
    bool bSyphon1A;
    bool bSyphon1S;
   
    bool bSyphon2A;
    bool bSyphon2S;
    
    bool bSyphon3A;
    bool bSyphon3S;
    
    void changeSyphon();
    bool bShowOne;
    bool bShowTwo;
    bool bShowThree;
    
    int frameRate;
    int showChannel;
    
    midiInput midi;
    
    ofFbo       fbo;
    ofFbo       maskFbo;
    ofShader    shader;
};

#endif

