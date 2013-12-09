#include "TestLayer2.h"

//--------------------------------------------------------------------------------------------------------------
void TestLayer2::setup(){
    ofSetFrameRate(30);
    flag = true;
    a = 150;
    b.loadMovie("kegonfalls_05.mp4");
    b.play();
    
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer2::update(){
    
    b.update();
    time = b.getPosition();
    
    //    if (time < (1*60+30)*30) {
    //    if (flag == false) {
    //
    //        if (a > 50) { a-=0.1; }else{ flag = true; }
    //
    //    }else{
    //        if (a < 220) { a+=0.1; }else{ flag = false; }
    //
    //    }
    //    }else{ a = 180; }
    //
    //
    //    if(time > (9*60+15)*30){ time = 0; }
    
}
//--------------------------------------------------------------------------------------------------------------
void TestLayer2::draw(){
    ofBackground(0,0,0,0);
    ofSetColor(90, 15, 15, a);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    //　　暗転　１
    if (time > 0.18 && time < 0.19608) {
        ofSetColor(0, 0, 0, 255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    //　暗転　２
    if (time > 0.716016 && time < 0.730039) {
        ofSetColor(0, 0, 0, 255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
}


