#include "TestLayer2.h"
#include "TestLayer3.h"
float time_;
//--------------------------------------------------------------------------------------------------------------
void TestLayer2::setup(){
    ofSetFrameRate(30);
//    flag = true;
    a = 150;
//    b.loadMovie("kegonfalls_05.mp4");
    
    
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer2::update(){
//    if (start_mov == true) {
//        b.play();
//        b.update();
//    }
    time_ = b.getPosition();
    
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
    
    //　　暗転　0
    if (time_ < 0.01) {
        ofSetColor(0, 0, 0, 255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    
    //　　暗転　１
    //　　0.195379　〜 0.203663
    if (time_ > 0.2 && time_ < 0.22) {
        ofSetColor(0, 0, 0, 255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    
    
    //　暗転　２
    //　0.726002　〜　0.739955
    if (time_ > 0.73 && time_ < 0.75) {
        ofSetColor(0, 0, 0, 255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    //　暗転　3
    //　0.914103　〜　0.92295
    if (time_ > 0.92 && time_ < 0.94) {
        ofSetColor(0, 0, 0, 255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    //　暗転　4
    //　0.973707
    
    if (time_ > 0.98) {
        ofSetColor(0, 0, 0, 255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
}


