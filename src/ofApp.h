#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxImageSequenceRecorder.h"

class ofApp : public ofBaseApp{

	public:
    
        bool bCalibrated;
        bool bSaving;
        int leftEyeLabel;
        int rightEyeLabel;
        int eyeBoxWidth;
        int eyeBoxHeight;
		ofVideoPlayer player;
        ofRectangle eyesBBox;
        ofRectangle leftEyeBox;
        ofRectangle rightEyeBox;
        ofImage leftEye;
        ofImage rightEye;
        ofxCv::ObjectFinder eyeFinder;
        ofxImageSequenceRecorder leftEyeRecorder;
        ofxImageSequenceRecorder rightEyeRecorder;
    
		void setup();
		void update();
		void draw();

        ofRectangle setEyeImage(
            cv::Mat &src
            , ofImage &dst
            , ofRectangle roi
            , int w
            , int h
        );

        void exit();
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
