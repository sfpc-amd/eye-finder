#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

//   if( !eyes_cascade.load(ofToDataPath("haarcascade_eye_tree_eyeglasses.xml")) ){ printf("--(!)Error loading\n"); return -1; };

    eyeFinder.setup("haarcascade_eye_tree_eyeglasses.xml");

    player.loadMovie("eyes.mov");
    player.setLoopState(OF_LOOP_NORMAL);
    
    vidWidth = player.getWidth();
    vidHeight = player.getHeight();
    
    player.play();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update();
    if(player.isFrameNew()) {
        cv::Mat src = ofxCv::toCv(player.getPixelsRef());
        eyeFinder.update(src);

        if(eyeFinder.size() >= 1) {
//            cv::Mat leftEyeMat;
//            cv::Rect leftEyeRect;
            ofRectangle leftEyeRect;

            
            // this seems a little silly, can't we just
            // pull a cv::Rect directly
            leftEyeRect = eyeFinder.getObject(1);
//            leftEyeMat = src(leftEyeRect);
            leftEye.setFromPixels(player.getPixelsRef());
            leftEye.crop(
                leftEyeRect.getX()
                , leftEyeRect.getY()
                , leftEyeRect.getWidth()
                , leftEyeRect.getHeight()
            );
            
//            ofxCv::toOf(leftEyeMat, leftEye);
        }
        
        if(eyeFinder.size() >= 2) {
        
        }

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    player.draw(0, 0);
    
//    ofSetColor(255);
//    eyeFinder.draw();

    leftEye.draw(0, 0);

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
