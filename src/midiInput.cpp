//
//  midiInput.cpp
//  BUILDINGSNDS
//
//  Created by werk on 22-12-12.
//
//

#include "midiInput.h"


midiInput::midiInput(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // ofAddListener(ofEvents().update, this, &midiInput::update);
    // print input ports to console
	midiIn.listPorts(); // via instance
    
	//ofxMidiIn::listPorts(); // via static as well
	
	// open port by number (you may need to change this)
	midiIn.openPort(0);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input");	// open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add testApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	//midiIn.setVerbose(true);
    
    roll = 0;
    maxMidi = 127;
    
    tiltCam = 0;
    bChangeColor = true;
    channelValue = 1;
    
}


int midiInput::channels(){
    if (midiMessage.channel == 10 &&(midiMessage.deltatime != prevDelta)){
        cout<<        channelValue<<endl;
    if (midiMessage.control == 110){
        channelValue = 1;
        
    }
        if (midiMessage.control == 111){
            channelValue = 2;
        }
        if (midiMessage.control == 112){
            channelValue = 3;
        }
    }
    return channelValue;
}



void midiInput::showMidi(){
    
    ofSetColor(255);
	
	// draw the last recieved message contents to the screen
	text << "Received: " << ofxMidiMessage::getStatusString(midiMessage.status);
	ofDrawBitmapString(text.str(), 20, 20);
	text.str(""); // clear
	
	text << "channel: " << midiMessage.channel;
	ofDrawBitmapString(text.str(), 20, 34);
	text.str(""); // clear
	
	text << "pitch: " << midiMessage.pitch;
	ofDrawBitmapString(text.str(), 20, 48);
	text.str(""); // clear
	ofRect(20, 58, ofMap(midiMessage.pitch, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "velocity: " << midiMessage.velocity;
	ofDrawBitmapString(text.str(), 20, 96);
	text.str(""); // clear
	ofRect(20, 105, ofMap(midiMessage.velocity, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "control: " << midiMessage.control;
	ofDrawBitmapString(text.str(), 20, 144);
	text.str(""); // clear
	ofRect(20, 154, ofMap(midiMessage.control, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "value: " << midiMessage.value;
	ofDrawBitmapString(text.str(), 20, 192);
	text.str(""); // clear
	if(midiMessage.status == MIDI_PITCH_BEND) {
		ofRect(20, 202, ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()-40), 20);
	}
	else {
		ofRect(20, 202, ofMap(midiMessage.value, 0, 127, 0, ofGetWidth()-40), 20);
	}
	
	text << "delta: " << midiMessage.deltatime;
	ofDrawBitmapString(text.str(), 20, 240);
	text.str(""); // clear
    

    
}


void midiInput::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}


//--------------------------------------------------------------
void midiInput::newMidiMessage(ofxMidiMessage& msg) {
    
	// make a copy of the latest message
	midiMessage = msg;
}



