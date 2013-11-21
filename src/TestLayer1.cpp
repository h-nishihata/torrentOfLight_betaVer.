

#include "TestLayer1.h"
void TestLayer1::update(){

}
void TestLayer1::draw()
{
    ofBackground(0, 0, 0, 0);
    ofSetColor(0, 255, 0);
    
    ofRect(ofGetMouseX(), ofGetMouseY(), 100, 100);
    
    ofDrawBitmapString(ofToString(__PRETTY_FUNCTION__), 10, 20 + 20 * getLayerIndex());
}