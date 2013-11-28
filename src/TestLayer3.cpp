#include "TestLayer3.h"

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::setup(){
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
    vidPlayer.loadMovie("kegonfalls.mp4");
    vidPlayer.play();
    
    colorImg.allocate(960,540);
    colorImgHSV.allocate(960,540);
    
	grayImage.allocate(960,540);
	grayBg.allocate(960,540);
	grayDiff.allocate(960,540);
    compositeImg.allocate(960,540);
    
	bLearnBakground = true;
	threshold = 100;
    
    for (int n=0; n<nPixels; n++) {
        r[n] = -100;
        g[n] = -150;
        b[n] = -130;
        a[n] = -100;
    }
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::update(){
    
    vidPlayer.update();
    
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
            compositeImgPixels[3*i] = sampleImgPixels[3*i]+r[i];
            compositeImgPixels[3*i+1] = sampleImgPixels[3*i+1]+g[i];
            compositeImgPixels[3*i+2] = sampleImgPixels[3*i+2]+b[i];
            compositeImgPixels[3*i+3] = sampleImgPixels[3*i+3]+a[i];
            
        }else{
            compositeImgPixels[3*i] = sampleImgPixels[3*i]+r[i];
            compositeImgPixels[3*i+1] = sampleImgPixels[3*i+1]+g[i];
            compositeImgPixels[3*i+2] = sampleImgPixels[3*i+2]+b[i];
            compositeImgPixels[3*i+3] = sampleImgPixels[3*i+3]+a[i];
            
        }
    }
    
    
    
    //          ********************   PHASE 1   ********************
    
    if(end0){
        if(time1 < 500){
            
            for (int i=0; i<nPixels; i++) {
                if (r[i]<255){ r[i]+0.5; }else{ r[i]=0; }
                if (g[i]<255){ g[i]+0.1; }else{ g[i]=0; }
                if (b[i]<255){ b[i]+0.5; }else{ b[i]=0; }
                if (a[i]>0){ a[i]--; }else{ a[i]=100; }
                
            }
            time1++;
            if(time1 == 200)bLearnBakground = true;
            if(threshold > 80) threshold --;
            
        }else{
            
            for (int i=0; i<nPixels; i++) {
                if (r[i]<255){ r[i]+0.5; }else{ r[i]=0; }
                if (g[i]<255){ g[i]+0.1; }else{ g[i]=0; }
                if (b[i]<255){ b[i]+0.1; }else{ b[i]=0; }
                if (a[i]>0){ a[i]--; }else{ a[i]=100; }
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
                if (r[i]<255){ r[i]+0.1; }else{ r[i]=0; }
                if (g[i]<255){ g[i]+0.5; }else{ g[i]=0; }
                if (b[i]<255){ b[i]+0.1; }else{ b[i]=0; }
                if (a[i]>0){ a[i]--; }else{ a[i]=100; }
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
                if (g[i]<255){ g[i]+0.1; }else{ g[i]=0; }
                if (b[i]<255){ b[i]+0.1; }else{ b[i]=0; }
                if (a[i]>0){ a[i]--; }else{ a[i]=100; }
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
                if (r[i]<255){ r[i]+0.1; }else{ r[i]=0; }
                if (g[i]<255){ g[i]+0.5; }else{ g[i]=0; }
                if (b[i]<255){ b[i]+0.1; }else{ b[i]=0; }
                if (a[i]>0){ a[i]--; }else{ a[i]=100; }
            }
            if(threshold > 30) threshold --;
            end2 = false;
            end4 = true;
            
        }
    }
    
    
    
    compositeImg.setFromPixels(compositeImgPixels,960,540);
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::draw(){
    
    //    ofBackground(0,0,0,0);
    ofSetColor(140, 140, 30);
    compositeImg.draw(-95,-50,ofGetWidth()*1.1,ofGetHeight()*1.1);
    
    //          ********************    CIRCLES     ********************
    
    
    int num = contourFinder.blobs.size();
    int centerX[num], centerY[num];
    int radius = ofRandom(40);
    
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for (int n=0; n<num; n++) {
        centerX[n] = contourFinder.blobs[n].boundingRect.x;
        centerY[n] = contourFinder.blobs[n].boundingRect.y;
        
        red = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 ];
        green = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 +1];
        blue = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 +2];
        
//        ofNoFill();
//        ofSetLineWidth(ofRandom(3,20));
        ofSetColor(red,green,blue);
        ofCircle(2*centerX[n],2*centerY[n],radius);
    }
}

