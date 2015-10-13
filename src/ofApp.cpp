#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    eyeBoxWidth = 120;
    eyeBoxHeight = 120;
    
    bCalibrated = false;
    bSaving = false;

    eyeFinder.setup("haarcascade_eye_tree_eyeglasses.xml");
    eyeFinder.setPreset(ofxCv::ObjectFinder::Fast);
    eyeFinder.setRescale(.5);

    player.loadMovie("eyes.mov");
    player.setLoopState(OF_LOOP_NONE);
//    eyesBBox = ofRectangle(100, 0, player.getWidth()-100, player.getHeight() - 150);
    
    player.play();
    
    ofDirectory::createDirectory("media/left", true, true);
    ofDirectory::createDirectory("media/right", true, true);
   
    leftEyeRecorder.setPrefix(ofToDataPath("media/left/frame_"));
    leftEyeRecorder.setFormat("png");
    rightEyeRecorder.setPrefix(ofToDataPath("media/right/frame_"));
    rightEyeRecorder.setFormat("png");
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
                
                bCalibrated = true;
                player.firstFrame();
            }
        // now show
        } else {
            
            if(tracker.existsCurrent(leftEyeLabel)) {
                leftEyeBox = setEyeImage(
                    src
                    , leftEye
                    , eyeFinder.getObjectSmoothed(eyeFinder.getLabel(leftEyeLabel))
                    , eyeBoxWidth
                    , eyeBoxHeight
                );
                leftEye.update();
            }
            
            if(tracker.existsCurrent(rightEyeLabel)) {
                rightEyeBox = setEyeImage(
                    src
                    , rightEye
                    , eyeFinder.getObjectSmoothed(eyeFinder.getLabel(rightEyeLabel))
                    , eyeBoxWidth
                    , eyeBoxHeight
                );
                rightEye.update();
            }
            
            if(bSaving) {
                leftEyeRecorder.addFrame(leftEye);
                rightEyeRecorder.addFrame(rightEye);

                if(player.getIsMovieDone()) {
                    leftEyeRecorder.stopThread();
                    rightEyeRecorder.stopThread();
                    bSaving = false;
                }
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
//        ofRect(eyesBBox);
        
        ofPushMatrix();
//            ofTranslate(eyesBBox.x, eyesBBox.y);
            ofDrawBitmapString("LEFT", leftEyeBox.getLeft(), leftEyeBox.getBottom());
            ofRect(leftEyeBox);
            
            ofDrawBitmapString("RIGHT", rightEyeBox.getLeft(), rightEyeBox.getBottom());
            ofRect(rightEyeBox);
        ofPopMatrix();
        leftEye.draw(0, player.getHeight());
        rightEye.draw(eyeBoxWidth, player.getHeight());
        
        ofDrawBitmapString(ofToString(eyeFinder.size()), 10, ofGetHeight());
        
        if(bSaving) {
            ofDrawBitmapString("SAVING", 20, 20);
        }
        
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


void ofApp::exit(){
    leftEyeRecorder.waitForThread();
    rightEyeRecorder.waitForThread();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'r') {
        player.firstFrame();
        player.play();
    } else if (key == 's') {
        if(!bSaving) {
            bSaving = true;
            player.firstFrame();
            player.setLoopState(OF_LOOP_NONE);

            if(!leftEyeRecorder.isThreadRunning()) {
                leftEyeRecorder.startThread(false, true);
            }
            if(!rightEyeRecorder.isThreadRunning()) {
                rightEyeRecorder.startThread(false, true);
            }

            player.play();
        }
    } else if (key == '1') {
        eyeFinder.setPreset(ofxCv::ObjectFinder::Fast);
        eyeFinder.setRescale(.5);
    } else if (key == '2') {
        eyeFinder.setPreset(ofxCv::ObjectFinder::Accurate);
    } else if (key == '3') {
        eyeFinder.setPreset(ofxCv::ObjectFinder::Sensitive);
    }
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
