#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

                ofxPanel _gui;
                ofParameterGroup parameters;
                ofParameter <int> teta1;
                ofParameter <int> teta2;

                ofPoint bras1L;
                ofPoint bras1H;

                ofPoint bras2L;
                ofPoint bras2H;

                ofPolyline bras1;
                ofPolyline bras2;

                int LArm1;
                int LArm2;

                ofTrueTypeFont	verdana14Font;

                // variables for torque calculation
                float teteW ;
                float rotationTeteServoW ;
                float inclinaisonTeteServoW ;
                float brasBasW  ;
                float brasHautW ;
                float inclinaisonBrasServoW ;
                float brasBasL ;
                float brasHautL ;

                float L5;
                float L4;
                float L3 ;
                float L2;
                float L6;

                float g;

                float totalHeadW;

                float T1Nm, T1KgCm, T2Nm, T2KgCm;
                float maxT1Nm, maxT1KgCm, maxT2Nm, maxT2KgCm;
                int teta1MaxT1, teta2MaxT1, teta1MaxT2, teta2MaxT2;

                float NeededT1Nm,  NeededT2Nm;

};
