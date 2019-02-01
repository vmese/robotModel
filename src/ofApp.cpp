#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);

    _gui.setup("Gui");
    _gui.setPosition(0 , 0);
    _gui.minimizeAll();

    verdana14Font.load("verdana.ttf", 14, true, true);
    verdana14Font.setLineHeight(18.0f);
    verdana14Font.setLetterSpacing(1.037);

    parameters.add(teta1.set("teta1",0,0,90));
    parameters.add(teta2.set("teta2",90,0,180));

    _gui.setup(parameters);


    // init variables for torquez calculation
    teteW = 200e-3 ;
    rotationTeteServoW = 55e-3 ;
    inclinaisonTeteServoW = 55e-3 + 28e-3 + 15e-3 ;
    brasBasL = 37e-2 ; //47e-2 ;
    brasHautL = 32e-2 ; //42e-2 ;
    brasBasW = 78e-3*brasBasL*2 + 56e-3*(brasBasL-0.024) ;
    brasHautW = 78e-3*brasHautL*2 + + 56e-3*(brasHautL-0.024);
    inclinaisonBrasServoW = 126e-3+35e-3+5e-3+33e-3;

    L5 = brasBasL + brasHautL;
    L4 = brasBasL + 0.5*brasHautL;
    L2 = 0.5*brasHautL;
    L6 = 0.5*brasBasL;

    g = 9.81;

    totalHeadW = teteW + rotationTeteServoW + inclinaisonTeteServoW;

     maxT1Nm = 0;
     maxT1KgCm = 0;
     maxT2Nm = 0 ;
     maxT2KgCm = 0;

     //
     LArm1 = ofGetWidth()/4*brasBasL*3;
     LArm2 = ofGetWidth()/4*brasHautL*3;

     bras1L.set(ofGetWidth()/2,ofGetHeight());
     bras1H.set(ofGetWidth()/2+LArm1,ofGetHeight());

     bras2L.set(bras1H.x,bras1H.y);
     bras2H.set(bras1H.x+L2,bras1H.y);

}

//--------------------------------------------------------------
void ofApp::update(){

    int x1 = ofGetWidth()/2 + LArm1 * cos((int)teta1*M_PI/180.0) ;
    int y1 = LArm1 * sin((int)teta1*M_PI/180.0) ;
    bras1H.set(x1,ofGetHeight()-y1);

    int x2 = LArm2 * cos((int)(teta1+teta2)*M_PI/180.0) ;
    int y2 = LArm2 * sin((int)(teta1+teta2)*M_PI/180.0) ;
    bras2L.set(bras1H.x,bras1H.y);
    bras2H.set(bras1H.x+x2,bras1H.y-y2);

    // calc torque
    float m1 = brasBasW + inclinaisonBrasServoW ;
    float m2 = brasHautW + totalHeadW ;

    float S1 = sin((int)(teta1-90)*M_PI/180);
    float S12 = sin((int)((teta1-90) + teta2)*M_PI/180);

    T1Nm = abs(m2*g*brasHautL*S12);
    T2Nm = abs((m1+m2)*g*brasBasL*S1 + m2*g*brasHautL*S12);

    T1KgCm = T1Nm/g*100 ;
    T2KgCm = T2Nm/g*100 ;

    if (T1Nm>=maxT1Nm)
    {
        maxT1Nm = T1Nm ;
        maxT1KgCm = T1KgCm ;
        teta1MaxT1 = teta1 ;
        teta2MaxT1 = teta2 ;
        NeededT1Nm = maxT1Nm *1.2 * 4;
    }
    if (T2Nm>=maxT2Nm)
    {
        maxT2Nm = T2Nm ;
        maxT2KgCm = T2KgCm ;
        teta1MaxT2 = teta1 ;
        teta2MaxT2 = teta2 ;
        NeededT2Nm = maxT2Nm *1.2 * 4;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    _gui.draw();
    ofDrawLine(bras1L,bras1H);
    ofDrawLine(bras2L,bras2H);
    ofDrawTriangle(bras2H.x,bras2H.y,bras2H.x-50,bras2H.y-50,bras2H.x-50,bras2H.y+50);

    verdana14Font.drawString("T1 Nm :" + ofToString(abs(T1Nm)),10,100);
    verdana14Font.drawString("T2 Nm :" + ofToString(abs(T2Nm)),10,150);

    ofSetColor(ofColor::red);
    verdana14Font.drawString("Needed T1 stall torque Nm :" + ofToString(T1Nm*1.2*4),10,200);
    verdana14Font.drawString("Needed T2 stall torque Nm :" + ofToString(T2Nm*1.2*4),10,250);
    ofSetColor(ofColor::white);

//    verdana14Font.drawString("T1 KgCm :" + ofToString(abs(T1KgCm)),10,200);
//    verdana14Font.drawString("T2 KgCm :" + ofToString(abs(T2KgCm)),10,250);

//    verdana14Font.drawString("Max T1 Nm :" + ofToString(maxT1Nm) + " - angles = " + ofToString(teta1MaxT1) + "," + ofToString(teta2MaxT1)  ,10,300);
//    verdana14Font.drawString("Max T2 Nm :" + ofToString(maxT2Nm) + " - angles = " + ofToString(teta1MaxT2) + "," + ofToString(teta2MaxT2),10,350);

//    verdana14Font.drawString("Max T1 KgCm :" + ofToString(maxT1KgCm) + " - angles = " + ofToString(teta1MaxT1) + "," + ofToString(teta2MaxT1) ,10,450);
//    verdana14Font.drawString("Max T2 KgCm :" + ofToString(maxT2KgCm) + " - angles = " + ofToString(teta1MaxT2) + "," + ofToString(teta2MaxT2),10,500);

//    ofSetColor(ofColor::red);
//    verdana14Font.drawString("Needed T1 stall torque Nm :" + ofToString(NeededT1Nm),10,550);
//    verdana14Font.drawString("Needed T2 stall torque Nm :" + ofToString(NeededT2Nm),10,600);
//    ofSetColor(ofColor::white);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
