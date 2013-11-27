#include "TestLayer2.h"
#include "TestLayer3.h"


void TestLayer2::setup(){
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
    vidPlayer.loadMovie("kegonfalls_01.mov");
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
void TestLayer2::update(){
    
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
    unsigned char* sampleImgPixels2 = colorImgHSV.getPixels();
    
    
    for (int i=0; i<nPixels; i++) {
        if (grayPixels[i] == 0) {
            compositeImgPixels[3*i] = (sampleImgPixels[3*i]+r[i])*2;
            compositeImgPixels[3*i+1] = (sampleImgPixels[3*i+1]+g[i])*2;
            compositeImgPixels[3*i+2] = (sampleImgPixels[3*i+2]+b[i])*2;
            compositeImgPixels[3*i+3] = (sampleImgPixels[3*i+3]+a[i])*2;
            
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
                if (b[i]<255){ b[i]++; }else{ b[i]=0; }
                if (a[i]>0){ a[i]--; }else{ a[i]=100; }
                
            }
            time1++;
            if(time1 == 200)bLearnBakground = true;
            if(threshold > 80) threshold --;
            
        }else{
            
            for (int i=0; i<nPixels; i++) {
                if (r[i]<255){ r[i]+0.5; }else{ r[i]=0; }
                if (g[i]<255){ g[i]+0.1; }else{ g[i]=0; }
                if (b[i]<255){ b[i]++; }else{ b[i]=0; }
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
                if (r[i]<255){ r[i]++; }else{ r[i]=0; }
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
                if (g[i]<255){ g[i]++; }else{ g[i]=0; }
                if (b[i]<255){ b[i]++; }else{ b[i]=0; }
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
                if (r[i]<255){ r[i]++; }else{ r[i]=0; }
                if (g[i]<255){ g[i]+0.5; }else{ g[i]=0; }
                if (b[i]<255){ b[i]++; }else{ b[i]=0; }
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
void TestLayer2::draw(){
//    ofTranslate(0, 900);
//    ofRotateX(180);
    
//    ofBackground(0,0,0,0);
    ofSetColor(140, 140, 50, 240);
    compositeImg.draw(0,0,ofGetWidth(),ofGetHeight());


    
    

}
