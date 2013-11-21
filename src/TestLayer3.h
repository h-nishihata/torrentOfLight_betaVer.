#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxLayer.h"
#define OFX_LAYER_DEFINE_LAYER_CLASS(Klass) public: const char* getClassName() const { return #Klass; } \
unsigned int getClassID() const { return ofx::Layer::Type2Int<Klass>::value(); }


class TestLayer3 : public ofxLayer::Layer{
public:
    
    OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer3)
    
    void setup();
    void update();
    void draw();
    
    ofVideoPlayer vidPlayer;
    
    ofxCvColorImage colorImg;
    ofxCvColorImage colorImgHSV;
    ofxCvColorImage colorImgRGB;
    
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvContourFinder contourFinder;
    
    ofxCvColorImage compositeImg;
    
    int threshold;
    bool bLearnBakground;
    
    int nPixels = 480*312;
    float r[480*312];
    float g[480*312];
    float b[480*312];
    unsigned char* compositeImgPixels = new unsigned char[nPixels*3];
    
    int time1 = 0;
    int time2 = 0;
    int time3 = 0;
    int time4 = 0;
    
    bool end0 = true;
    bool end1 = false;
    bool end2 = false;
    bool end3 = false;
    bool end4 = false;
    
};