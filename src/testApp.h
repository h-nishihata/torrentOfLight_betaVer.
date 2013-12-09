//#pragma once
#include "ofMain.h"
#include "ofxLayer.h"

#include "TestLayer1.h"
#include "TestLayer2.h"
#include "TestLayer3.h"



class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    
    TestLayer1 *layer1;
    TestLayer2 *layer2;
    TestLayer3 *layer3;
    
    ofxLayer::Manager mng;
//    int time_ = TestLayer3.;
};

