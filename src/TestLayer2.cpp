

#include "TestLayer2.h"

void TestLayer2::update(){

}
void TestLayer2::draw()
{
    ofBackground(0, 0, 0, 0);
    ofSetColor(255, 0, 0);
    ofRect(ofGetMouseX() + 10, ofGetMouseY() + 10, 100, 100);
    
    ofDrawBitmapString(ofToString(__PRETTY_FUNCTION__), 10, 20 + 20 * getLayerIndex());
}
