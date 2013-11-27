#include "testApp.h"

//--------------------------------------------------------------------------------------------------------------
void testApp::setup(){

    ofSetVerticalSync(true);
    ofBackground(50);
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
    
//        ofTranslate(0,ofGetHeight(),0);
//        ofRotateZ(-90);
    
    ofEnableAlphaBlending();
    mng.draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
//    if (key == '1') layer1->moveUp();
//    if (key == '2') layer1->moveDown();

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
