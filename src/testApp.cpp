#include "testApp.h"

const int width = 800;
const int height = 600;

//--------------------------------------------------------------
void testApp::setup(){
	counter = 0;
	//ofSetCircleResolution(50);
	
    //ofBackground(0,0,0);
    
	
    bSmooth = false;
//	ofSetWindowTitle("graphics example");
    
	mainOutputSyphonServer.setName("WEKILLBOMBS combined output");
    
    
	//individualTextureSyphonServer.setName("Texture Output");

	mClient.setup();
    
       mClient.setApplicationName("BUILDINGSNDS");
    mClient.setServerName("Buildings NDS");

    
    mClient2.setup();
    
   // mClient2.setApplicationName("Modul8");
    mClient2.setServerName("Main View");
    
    
    mClient3.setup();
    
    //mClient3.setApplicationName("ClubNight6_2b");
    mClient3.setServerName("FFTplain");

    screen = 1;
	
    tex.allocate(width, height, GL_RGBA);
    
   font. loadFont("Swiss924.ttf", 42);
    
	ofSetFrameRate(15); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    setGUI2();
    
     bSyphon1A = false;
     bSyphon2A = false;
     bSyphon3A = false;
    
    
    bSyphon1S = false;
    bSyphon2S = false;
    bSyphon3S = false;
    
    bShowOne = true;
    bShowTwo = false;
    bShowThree = false;
    
    frameRate = 20;
    showChannel = 1;
    
    /*
    string shaderProgram = STRINGIFY(
                                     uniform sampler2DRect tex0;
                                     uniform sampler2DRect tex1;
                                     uniform sampler2DRect tex2;
                                     
                                     
                                     void main (void){
                                         vec2 pos = gl_TexCoord[0].st;
                                         
                                         vec4 rTxt = texture2DRect(tex0, pos);
                                         vec4 gTxt = texture2DRect(tex1, pos);
                                         vec4 bTxt = texture2DRect(tex2, pos);
                                         vec4 mask = texture2DRect(maskTex, pos);
                                         
                                         vec4 color = vec4(0,0,0,0);
                                         color = mix(color, rTxt, mask.r );
                                         color = mix(color, gTxt, mask.g );
                                         color = mix(color, bTxt, mask.b );
                                         
                                         gl_FragColor = color;
                                     }
                                     );
    */
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){
	//counter = counter + 0.033f;
    ofSetFrameRate(frameRate);
    showChannel = midi.channels();
    

    
//    fbo.begin();
//    ofClear(0, 0, 0,255);
//    shader.begin();
//     mClient.bind();
//     mClient2.bind();
//    // Pass the syphon1 texture
//    shader.setUniformTexture("tex0", mClient.mTex , 1 );
//    // Pass the syphon2 texture
//    shader.setUniformTexture("tex1", mClient2.mTex , 2 );
//
//
//       mClient.unbind();
//    mClient2.unbind();
//    shader.end();
//    fbo.end();


    
}

//--------------------------------------------------------------
void testApp::draw(){
    changeSyphon();
	ofBackground(255, 0, 0);
    
    
    individualTextureSyphonServer.publishTexture(&fbo.getTextureReference());
     
    if (showChannel == 1){
        mClient.bind();
        individualTextureSyphonServer.publishTexture(&mClient.mTex );
        mClient.unbind();
            
        }
    if( showChannel == 2){
            mClient2.bind();
            individualTextureSyphonServer.publishTexture(&mClient2.mTex);
            mClient2.unbind();
            
        }
    if ( showChannel == 3)
        
        {
            mClient3.bind();
            individualTextureSyphonServer.publishTexture(&mClient3.mTex);
            mClient3.unbind();
            
        } 
   midi.showMidi();
//
    ofPushMatrix();
  ofFill();
    ofSetColor(255,255,255);
    
    font.drawString(ofToString(showChannel), 100,100);
  
    ofPopMatrix();
   // ofDrawBitmapString("Note this text is not captured by Syphon since it is drawn after publishing.\nYou can use this to hide your GUI for example.",);
    

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    
  
	if (key == '1'){
        showChannel = 1;
		bShowOne = !bShowOne;
	}
    if (key == '2'){
         showChannel = 2;
        bShowTwo = !bShowTwo;
	}
    if (key == '3'){
        showChannel = 3;
		bShowThree = !bShowThree;
	}
}


void testApp::changeSyphon(){
    if ( bSyphon1A && (bSyphon1S)){
        
        cout<<"bSyphon1"<<endl;
             mClient = *new ofxSyphonClient;
        mClient.setup();
        
        mClient.setApplicationName(SYPHON1app);
        mClient.setServerName(SYPHON1syphon);
        bSyphon1A = false;
        bSyphon1S = false;
    }
    
 if ( bSyphon2A && (bSyphon2S)){                cout<<"bSyphon2"<<endl;
        mClient2 = *new ofxSyphonClient;
        mClient2.setup();
        
        mClient2.setApplicationName(SYPHON2app);
        mClient2.setServerName(SYPHON2syphon);
     bSyphon2A = false;
     bSyphon2S = false;
     
    }
    
    if ( bSyphon3A && (bSyphon3S)){
                  cout<<"bSyphon2"<<endl;
             mClient3 = *new ofxSyphonClient;
        mClient3.setup();
        
        mClient3.setApplicationName(SYPHON3app);
        mClient3.setServerName(SYPHON3syphon);
         bSyphon3A = false;
          bSyphon3S = false;
        
    }
    
    
}


void testApp::guiEvent(ofxUIEventArgs &e)
{
      ofxUITextInput *textinput = (ofxUITextInput *) e.widget;

    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
        string output = textinput->getTextString();
    cout << output << endl;
 
    if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
    {
        cout<<"ENTER"<<endl;
    
        if(name == "SYPHON1app")
            {
                cout<<"!!!"<<endl;
        SYPHON1app = output;
        bSyphon1A = true;
            }
        if(name == "SYPHON1syphon")
        {
               cout<<"!!!"<<endl;
            SYPHON1syphon = output;
                  bSyphon1S = true;
        }
        
        
        
        
        
        if(name == "SYPHON2app")
        {
               cout<<"!!!"<<endl;
            SYPHON2app = output;
            bSyphon2A = true;
        }
        if(name == "SYPHON2syphon")
        {
               cout<<"!!!"<<endl;
            SYPHON2syphon = output;
            bSyphon2S = true;
        }
        
        
        
        
        
        
        if(name == "SYPHON3app")
        {
               cout<<"!!!"<<endl;
            SYPHON3app = output;
          bSyphon3A = true;
        }
        if(name == "SYPHON3syphon")
        {
               cout<<"!!!"<<endl;
            SYPHON3syphon = output;
             bSyphon3S = true;
        }
        
   
        
        
        
    
    }
    

}

void testApp::setGUI2()
    {
        float dim = 16;
        float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
        float length = 255-xInit;
        
  
        
        gui2 = new ofxUICanvas(length+xInit+2, 0, length+xInit, ofGetHeight());
        gui2->addSpacer(length-xInit, 2);
        gui2->addLabel("1 APP");
        gui2->addTextInput("SYPHON1app","BUILDINGSNDS", length-xInit)->setAutoClear(false);
        gui2->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
            gui2->addLabel("1 SYPHON");

        gui2->addTextInput("SYPHON1syphon","Buildings NDS", length-xInit)->setAutoClear(false);
        
          gui2->addSpacer(length-xInit, 2);
        gui2->addLabel("2 APP");
        gui2->addTextInput("SYPHON2app","Modul8", length-xInit)->setAutoClear(false);
        gui2->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
        gui2->addLabel("2 SYPHON");
        gui2->addTextInput("SYPHON2syphon","Main View", length-xInit)->setAutoClear(false);
        
        
        
        
          gui2->addSpacer(length-xInit, 2);
        gui2->addLabel("3 APP");
        gui2->addTextInput("SYPHON3app","FFTplain", length-xInit)->setAutoClear(false);
        gui2->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
        gui2->addLabel("3 SYPHON");
        gui2->addTextInput("SYPHON3syphon","plainOut", length-xInit)->setAutoClear(false);
      
        
        
        
        ofAddListener(gui2->newGUIEvent,this,&testApp::guiEvent);

}




void testApp::exit(){
    midi.exit();
    
    
}


