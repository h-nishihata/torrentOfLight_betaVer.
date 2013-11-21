#include "ofMain.h"
#include "ofxLayer.h"
#define OFX_LAYER_DEFINE_LAYER_CLASS(Klass) public: const char* getClassName() const { return #Klass; } \
unsigned int getClassID() const { return ofx::Layer::Type2Int<Klass>::value(); }

class TestLayer2 : public ofxLayer::Layer
{
public:
    
    OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer2)
    
    void update();
    
    void draw();
};