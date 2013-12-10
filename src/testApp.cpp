#include "testApp.h"

bool start_mov;
//--------------------------------------------------------------------------------------------------------------
void testApp::setup(){
    sender.setup(HOST, PORT);
    ofSetVerticalSync(true);
    ofBackground(100,100,5);
    mng.setup(1440,900);
    
    layer1 = mng.createLayer<TestLayer1>();
    layer2 = mng.createLayer<TestLayer2>();
    layer3 = mng.createLayer<TestLayer3>();
    
    layer1->setVisible(true);
    layer1->setAlpha(255);
    
    layer2->setVisible(true);
    layer2->setAlpha(255);
    
    layer3->setVisible(true);
    layer3->setAlpha(255);
}

//--------------------------------------------------------------------------------------------------------------
void testApp::update(){
    
    mng.update();
    
}

//--------------------------------------------------------------------------------------------------------------
void testApp::draw(){
    
    ofEnableAlphaBlending();
    mng.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == ' ') {
        
        start_mov = true;
        
        ofxOscMessage m;
        
        m.setAddress("/mouse/position");
        
        m.addIntArg(key);
        
        sender.sendMessage(m);
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
