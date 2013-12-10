#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxLayer.h"
#define OFX_LAYER_DEFINE_LAYER_CLASS(Klass) public: const char* getClassName() const { return #Klass; } \
unsigned int getClassID() const { return ofx::Layer::Type2Int<Klass>::value(); }

extern bool start_mov;
extern     float time_;
class TestLayer3 : public ofxLayer::Layer{
public:
    
    OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer3)
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    ofVideoPlayer vidPlayer;
    
    ofxCvColorImage colorImg;
    ofxCvColorImage colorImgHSV;
    ofxCvColorImage colorImgRGB;
    
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvContourFinder contourFinder;
    
    ofxCvColorImage compositeImg;
    
    float threshold;
    bool bLearnBakground;
    
    int nPixels = 960*540;
    float r[960*540];
    float g[960*540];
    float b[960*540];
    float a[960*540];
    
    float r_;
    float g_;
    float b_;
    
    unsigned char* compositeImgPixels = new unsigned char[nPixels*3];
    
//    float time_;
    
    
    bool end0 = true;
    bool end1 = false;
    bool end2 = false;
    bool end3 = false;
    bool end4 = false;
    
};