#include "TestLayer3.h"

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::setup(){
    ofSetFrameRate(30);
    
    
    vidPlayer.loadMovie("kegonfalls_05.mp4");
    
    
    colorImg.allocate(960,540);
    colorImgHSV.allocate(960,540);
    
	grayImage.allocate(960,540);
	grayBg.allocate(960,540);
	grayDiff.allocate(960,540);
    compositeImg.allocate(960,540);
    
	bLearnBakground = true;
	threshold = 240;
    
    for (int n=0; n<nPixels; n++) {
        r[n] = -100;
        g[n] = -170;
        b[n] = -200;
        
        a[n] = 0;
    }
    
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::update(){
    ofEnableAlphaBlending();
    if (start_mov == true) {
        vidPlayer.play();
        vidPlayer.update();
    }
    time_ = vidPlayer.getPosition();
    //    cout<<time_<<endl;
    //      ********************    CONVERT IMAGE   ********************
    
    colorImg.setFromPixels(vidPlayer.getPixels(), 960,540);
    colorImgHSV = colorImg;
    colorImgHSV.convertRgbToHsv();
    
    grayImage = colorImg;
    
    if (bLearnBakground == true){
        grayBg = grayImage;
        bLearnBakground = false;
    }
    
    grayDiff.absDiff(grayBg, grayImage);
    grayDiff.threshold(threshold);
    
    contourFinder.findContours(grayDiff, 20, (960*540)/3, 10, true);
	
    colorImgRGB = colorImg;
    colorImgRGB.convertHsvToRgb();
    
    
    
    //          ********************  COLORING ROUTINES   ********************
    
    unsigned char* grayPixels = grayDiff.getPixels();
    unsigned char* sampleImgPixels = colorImgRGB.getPixels();
    //    unsigned char* sampleImgPixels2 = colorImgHSV.getPixels();
    
    
    
    for (int i=0; i<nPixels; i++) {
        if (grayPixels[i] == 0) {
            compositeImgPixels[3*i] = 90;
            compositeImgPixels[3*i+1] = 15;
            compositeImgPixels[3*i+2] = 15;
            compositeImgPixels[3*i+3] = 50;
            
        }else{
            compositeImgPixels[3*i] = sampleImgPixels[3*i]+r[i];
            compositeImgPixels[3*i+1] = sampleImgPixels[3*i+1]+g[i];
            compositeImgPixels[3*i+2] = sampleImgPixels[3*i+2]+b[i];
            compositeImgPixels[3*i+3] = sampleImgPixels[3*i+3]+a[i];
            
        }
    }
    
    
    
    
    //          ********************   PHASE 1   ********************
    
    if (end0 == true) {
        if(time_ < 0.01){
            
            if(threshold < 235) threshold += 10;
            
        }else{
            //　上昇　１
            if(threshold > 0) threshold -= 5;
            
            end1 = true;
        }
    }
    
    //          ********************   PHASE 2   ********************
    
    
    if (end1 == true) {
        if (time_ < 0.5) {
            
        }else{
            for (int i=0; i<nPixels; i++) {
                if (r[i]<0){ r[i]+=0.1; }else{ r[i]=-200; }
                if (g[i]<0){ g[i]+=0.05; }else{ g[i]=-200; }
                if (b[i]<0){ b[i]+=0.05; }else{ b[i]=-200; }
                if (a[i]<0){ a[i]++; }else{ a[i]=-200; }
            }
            if(threshold < 150) threshold ++;
            end0 = false;
            end3 = true;
        }
    }
    
    //          ********************   PHASE 3   ********************
    
    if (end2 == true){
        
        if (time_ < 0.6) {
        }else{
            //　上昇　２
            for (int i=0; i<nPixels; i++) {
                if (grayPixels[i] == 0) {
                    compositeImgPixels[3*i] = sampleImgPixels[3*i];
                    compositeImgPixels[3*i+1] = sampleImgPixels[3*i+1];
                    compositeImgPixels[3*i+2] = sampleImgPixels[3*i+2];
                    compositeImgPixels[3*i+3] = sampleImgPixels[3*i+3];
                    
                }
            }
            for (int i=0; i<nPixels; i++) {
                if (r[i]<0){ r[i]++; }else{ r[i]=-200; }
                if (g[i]<0){ g[i]++; }else{ g[i]=-200; }
                if (b[i]<0){ b[i]++; }else{ b[i]=-200; }
                if (a[i]<0){ a[i]++; }else{ a[i]=-200; }
            }
            
            if(threshold < 240) threshold +=10;
            end1 = false;
            end3 = true;
        }
    }
    
    //          ********************   PHASE 4   ********************
    
    if (end3 == true){
        
        if (time_ < 0.72) {
            
        }else{
            if(threshold > 20) threshold --;
            for (int i=0; i<nPixels; i++) {
                if (grayPixels[i] == 0) {
                    compositeImgPixels[3*i] = sampleImgPixels[3*i]*2;
                    compositeImgPixels[3*i+1] = sampleImgPixels[3*i+1]*2;
                    compositeImgPixels[3*i+2] = sampleImgPixels[3*i+2]*2;
                    compositeImgPixels[3*i+3] = sampleImgPixels[3*i+3];
                    
                }
            }
            for (int i=0; i<nPixels; i++) {
                if (r[i]<0){ r[i]+=0.1; }else{ r[i]=-200; }
                if (g[i]<0){ g[i]++; }else{ g[i]=-200; }
                if (b[i]<0){ b[i]+=0.5; }else{ b[i]=-200; }
                if (a[i]<0){ a[i]++; }else{ a[i]=-200; }
            }
            
            end2 = false;
            end4 = true;
            
        }
    }
    
    //  reset
    if(end4 == true){
        if(time_ == 0){
            
        }else{
            end1 = end2 = end3 = end4 = false;
            end0 = true;
        }
    }
    
    
    compositeImg.setFromPixels(compositeImgPixels,960,540);
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::draw(){
    
    ofEnableAlphaBlending();
    ofBackground(0,0,0,0);
    compositeImg.draw(-95,-50,ofGetWidth()*1.2,ofGetHeight()*1.1);
    
    //          ********************    CIRCLES     ********************
    
    
    int num = contourFinder.blobs.size();
    int centerX[num], centerY[num];
    
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    
    for (int n=0; n<num; n++) {
        centerX[n] = contourFinder.blobs[n].boundingRect.x;
        centerY[n] = contourFinder.blobs[n].boundingRect.y;
        
        red = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 ];
        green = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 +1];
        blue = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 +2];
        
        ofNoFill();
        ofSetLineWidth(ofRandom(1,5));
        ofSetColor(red,green,blue);
        ofCircle(2*centerX[n],2*centerY[n],50*(red+green+blue)/765);
        ofCircle(2*centerX[n]+ofRandom(-5,5),2*centerY[n]+ofRandom(-5,5),60*(red+green+blue)/765);
        ofCircle(2*centerX[n]+ofRandom(-5,5),2*centerY[n]+ofRandom(-5,5),60*(red+green+blue)/765);
        ofCircle(2*centerX[n]+ofRandom(-5,5),2*centerY[n]+ofRandom(-5,5),60*(red+green+blue)/765);
    }
    
}




