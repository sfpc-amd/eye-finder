#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp{

	public:
    
        bool bCalibrated;
        int leftEyeLabel;
        int rightEyeLabel;
		ofVideoPlayer player;
        ofImage leftEye;
        ofImage rightEye;
        ofxCv::ObjectFinder eyeFinder;
    
		void setup();
		void update();
		void draw();

        void setEyeImage(
            cv::Mat &src
            , ofImage &dst
            , ofRectangle roi
            , int w
            , int h
        );

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


};
