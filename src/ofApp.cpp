#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    eyeBoxWidth = 120;
    eyeBoxHeight = 120;
    
    bCalibrated = false;

//   if( !eyes_cascade.load(ofToDataPath("haarcascade_eye_tree_eyeglasses.xml")) ){ printf("--(!)Error loading\n"); return -1; };

    eyeFinder.setup("haarcascade_eye_tree_eyeglasses.xml");
    eyeFinder.setPreset(ofxCv::ObjectFinder::Accurate);

    player.loadMovie("eyes.mov");
    player.setLoopState(OF_LOOP_NORMAL);
    
    player.play();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update();
    
    if(player.isFrameNew()) {
        cv::Mat src = ofxCv::toCv(player.getPixelsRef());
        eyeFinder.update(src);
        ofxCv::RectTracker tracker = eyeFinder.getTracker();
        
        // do some basic calibration
        if(!bCalibrated) {
            if(eyeFinder.size() >= 2) {
                if(eyeFinder.getObject(0).x < eyeFinder.getObject(1).x){
                    leftEyeLabel = eyeFinder.getLabel(0);
                    rightEyeLabel = eyeFinder.getLabel(1);
                } else {
                    leftEyeLabel = eyeFinder.getLabel(1);
                    rightEyeLabel = eyeFinder.getLabel(0);
                }
                
                printf("labels, %i, %i", leftEyeLabel, rightEyeLabel);
                
            }
            bCalibrated = true;
            player.firstFrame();
            
        // now show
        } else {
            if(tracker.existsCurrent(leftEyeLabel)) {
                leftEyeBox = setEyeImage(
                    src
                    , leftEye
                    , eyeFinder.getObject(eyeFinder.getLabel(leftEyeLabel))
                    , eyeBoxWidth
                    , eyeBoxHeight
                );
                leftEye.update();
            }
            
            if(tracker.existsCurrent(rightEyeLabel)) {
                rightEyeBox = setEyeImage(
                    src
                    , rightEye
                    , eyeFinder.getObject(eyeFinder.getLabel(rightEyeLabel))
                    , eyeBoxWidth
                    , eyeBoxHeight
                );
                rightEye.update();
            }
        }
    


    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);


    if(bCalibrated) {
        player.draw(0, 0);
        ofSetColor(255);
        ofNoFill();
        ofRect(leftEyeBox);
        ofRect(rightEyeBox);
        
//        leftEye.draw(0, 100);
//        rightEye.draw(ofGetWidth() - rightEye.getWidth(), 100);
    } else {
        ofDrawBitmapString("Calibrating...", 20, 20);
    }
}

ofRectangle ofApp::setEyeImage(cv::Mat &src, ofImage &dst, ofRectangle roi, int w, int h) {

    cv::Mat crop;
    cv::Size srcSize = src.size();
    ofPoint center = roi.getCenter();
    
    roi.setFromCenter(center.x, center.y, w, h);

    if(roi.getRight() > srcSize.width) {
        roi.translateX(-roi.getRight());
    }
    if(roi.getLeft() < 0) {
        roi.translateX(-roi.getLeft());
    }
    
    if(roi.getBottom() > srcSize.height) {
        roi.translateY(-roi.getBottom());
    }
    if(roi.getTop() < 0) {
        roi.translateY(-roi.getTop());
    }


    cv::Mat(src, ofxCv::toCv(roi)).copyTo(crop);
    ofxCv::toOf(crop, dst);
    
    return roi;
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
