#include "testApp.h"

//--------------------------------------------------------------------------------------------------------------
void testApp::setup(){
    
    // ADDED!

    ofSetFrameRate(15);
    ofEnableAlphaBlending();
    
    
    vidPlayer.loadMovie("kegonfalls.mov");
    vidPlayer.play();
    
    colorImg.allocate(480,312);
    colorImgHSV.allocate(480,312);
    
	grayImage.allocate(480,312);
	grayBg.allocate(480,312);
	grayDiff.allocate(480,312);
    compositeImg.allocate(480, 312);
    
    
	bLearnBakground = true;
	threshold = 100;
}

//--------------------------------------------------------------------------------------------------------------
void testApp::update(){
    
    vidPlayer.update();
    for (int i = 0; i < NUM; i++) {
        p[i].update();
    }
    
    
    
    //      ********************    CONVERT IMAGE   ********************
    
    colorImg.setFromPixels(vidPlayer.getPixels(), 480,312);
    colorImgHSV = colorImg;
    colorImgHSV.convertRgbToHsv();
    
    grayImage = colorImg;
    
    if (bLearnBakground == true){
        grayBg = grayImage;
        bLearnBakground = false;
    }
    
    grayDiff.absDiff(grayBg, grayImage);
    grayDiff.threshold(threshold);
    
    contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);
	
    colorImgRGB = colorImg;
    colorImgRGB.convertHsvToRgb();
    
    
    
    //          ********************  COLORING ROUTINES   ********************
    
    unsigned char* grayPixels = grayDiff.getPixels();
    unsigned char* sampleImgPixels = colorImgRGB.getPixels();
    unsigned char* sampleImgPixels2 = colorImgHSV.getPixels();

    
    for (int i=0; i<nPixels; i++) {
        if (grayPixels[i] == 0) {
            compositeImgPixels[3*i] = 140;
            compositeImgPixels[3*i+1] = 140;
            compositeImgPixels[3*i+2] = 10;
        }else{
            compositeImgPixels[3*i] = sampleImgPixels[3*i]+r[i];
            compositeImgPixels[3*i+1] = sampleImgPixels[3*i+1]+g[i];
            compositeImgPixels[3*i+2] = sampleImgPixels[3*i+2]+b[i];
        }
    }
    
    
    
    //          ********************   PHASE 1   ********************
    if(end0){
        if(time1 < 500){
            for (int i=0; i<nPixels; i++) {
                if (g[i]<255){ g[i]++; }else{ g[i]=0; }
            }
            time1++;
            if(time1 == 200)bLearnBakground = true;
            if(threshold > 80) threshold --;
        }else{
            for (int i=0; i<nPixels; i++) {
                if (r[i]<255){ r[i]+0.5; }else{ r[i]=0; }
                if (g[i]<255){ g[i]+0.1; }else{ g[i]=0; }
                if (b[i]<255){ b[i]++; }else{ b[i]=0; }
            }
            if(threshold >= 0) threshold --;
            end1 = true;
        }
    }
    
    //          ********************   PHASE 2   ********************
    if (end1 == true){
        if (time2 < 500) {
            time2++;
        }else{

            for (int i=0; i<nPixels; i++) {
                if (r[i]<255){ r[i]++; }else{ r[i]=0; }
                if (g[i]<255){ g[i]+0.5; }else{ g[i]=0; }
                if (b[i]<255){ b[i]+0.1; }else{ b[i]=0; }
            }
            if(threshold < 20) threshold ++;
            end0 = false;
            end2 = true;
        }
    }
    
    //          ********************   PHASE 3   ********************
    if (end2 == true){
        if (time3 < 500) {
            time3++;
        }else{
            for (int i=0; i<nPixels; i++) {
                if (r[i]<255){ r[i]+0.5; }else{ r[i]=0; }
                if (g[i]<255){ g[i]++; }else{ g[i]=0; }
                if (b[i]<255){ b[i]++; }else{ b[i]=0; }
            }
            if(threshold < 100) threshold +=2;
            end1 = false;
            end3 = true;
        }
    }
    
    //          ********************   PHASE 4   ********************
    if (end3 == true){
        if (time4 < 500) {
            time4++;
        }else{
            for (int i=0; i<nPixels; i++) {
                if (r[i]<255){ r[i]++; }else{ r[i]=0; }
                if (g[i]<255){ g[i]+0.5; }else{ g[i]=0; }
                if (b[i]<255){ b[i]++; }else{ b[i]=0; }
            }
            if(threshold > 30) threshold --;
            end2 = false;
            end4 = true;
        }
    }
    
    
    
    compositeImg.setFromPixels(compositeImgPixels,480,312);
}

//--------------------------------------------------------------------------------------------------------------
void testApp::draw(){
    
        ofTranslate(0,ofGetHeight(),0);
        ofRotateZ(-90);
    
    ofBackground(0);
    ofSetColor(255);
    
    compositeImg.draw(0,0,ofGetWidth(),ofGetHeight());
    contourFinder.draw(0,0,ofGetWidth(),ofGetHeight());
    
    
    
    //          ********************    PARTICLES     ********************
    
    //        ofSetColor(0, 0, 0, 100);
    //        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    //        for (int i = 0; i < NUM; i++) {
    //            p[i].draw();
    //        }
    
    
    
    
    //          ********************    CIRCLES     ********************
    
    int num = contourFinder.blobs.size();
    float x[num], y[num];
    float centerX[num], centerY[num];
    int radius = ofRandom(10,30);
    
    for (int i=0; i<num; i++) {
        //        if (contourFinder.blobs[i].boundingRect.x>100) {
        
        centerX[i] = contourFinder.blobs[i].boundingRect.x*3;
        centerY[i] = contourFinder.blobs[i].boundingRect.y*2.9;
        int pos = (centerY[i] * ofGetWidth()) + centerX[i];
        
        for (float ang=0; ang<=360; ang++) {
            x[i] = centerX[i] + (radius * cos(ang)) + ofRandom(0,5);
            y[i] = centerY[i] + (radius * sin(ang)) + ofRandom(0,5);
            ofSetColor(r[pos],g[pos],b[pos],ofRandom(10,100));
            ofEllipse(x[i],y[i],2,2);
        }
        
        //        }
    }
    
    
    
    //	colorImg.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
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
