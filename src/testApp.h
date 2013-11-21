//#pragma once
#include "ofMain.h"

#include "ofxLayer.h"

#include "TestLayer1.h"
#include "TestLayer2.h"
#include "TestLayer3.h"

#include "particle.h"
#define NUM 10000

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
    
//    ofVideoPlayer vidPlayer;
//    
//    ofxCvColorImage colorImg;
//    ofxCvColorImage colorImgHSV;
//    ofxCvColorImage colorImgRGB;
//    
//    ofxCvGrayscaleImage grayImage;
//    ofxCvGrayscaleImage grayBg;
//    ofxCvGrayscaleImage grayDiff;
//    ofxCvContourFinder contourFinder;
//    
//    ofxCvColorImage compositeImg;
//    
//    int threshold;
//    bool bLearnBakground;
//    
//    int nPixels = 480*312;
//    float r[480*312];
//    float g[480*312];
//    float b[480*312];
//    unsigned char* compositeImgPixels = new unsigned char[nPixels*3];
//    
//    int time1 = 0;
//    int time2 = 0;
//    int time3 = 0;
//    int time4 = 0;
//    
//    bool end0 = true;
//    bool end1 = false;
//    bool end2 = false;
//    bool end3 = false;
//    bool end4 = false;

    particle p[NUM];
    
    TestLayer1 *layer1;
    TestLayer2 *layer2;
    TestLayer3 *layer3;
    
    ofxLayer::Manager mng;
};

