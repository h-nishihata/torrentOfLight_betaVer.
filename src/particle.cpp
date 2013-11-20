#include "particle.h"



particle::particle(){
    
        x = ofRandom(ofGetWidth());
        y = ofRandom(ofGetHeight(),ofGetHeight()*1.5);
        r = ofRandom(8,20);
    int red = ofRandom(255);
    int blue = ofRandom(255);
    int green = ofRandom(255);
    }

//--------------------------------------------------------------
    void particle::draw(){
        
        ofFill();
        ofSetColor(255,0,0);
        ofEllipse(x, y, r, r);
    }

//--------------------------------------------------------------
    void particle::update(){
        
        int posx = ofRandom(-5,5);
        int posy = ofRandom(-20);
        x += posx;
        y += posy;
        
        //    if (y <= 0) {
        //        y = ofGetHeight();
        //    }
        
}