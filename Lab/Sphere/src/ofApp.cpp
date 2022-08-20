#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(ofColor::black);
	theCam = &easyCam;
	easyCam.setDistance(10);
	easyCam.setNearClip(.1);
	sideCam.setPosition(glm::vec3(5, 0, 0));
	sideCam.lookAt(glm::vec3(0, 0, 0));
	sideCam.setNearClip(.1);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	theCam->begin();
	drawAxis();
	ofNoFill();
	// main sphere
	ofSetColor(ofColor::lightGray);
	ofDrawSphere(glm::vec3(.5, .5, .5), 1.0);

	// selection point
	if (selected) {
		ofSetColor(ofColor::purple);
		ofDrawSphere(intersectPt, .1);
	}

	
	theCam->end();
}

void ofApp::drawAxis() {
	ofSetColor(ofColor::red);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	ofSetColor(ofColor::green);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	ofSetColor(ofColor::blue);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
	ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_F1:
		theCam = &easyCam;
		break;
	case OF_KEY_F2:
		theCam = &sideCam;
		break;
	default:
		break;
	}
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
	glm::vec3 screen3DPt = theCam->screenToWorld(glm::vec3(x, y, 0));
	glm::vec3 rayOrigin = theCam->getPosition();
	glm::vec3 rayDir = glm::normalize(screen3DPt - rayOrigin);
	glm::vec3 intersectNormal;
	bool bIntersect = glm::intersectRaySphere(rayOrigin, rayDir, glm::vec3(.5, .5, .5), 1.0,
		intersectPt, intersectNormal);
	if (bIntersect) {
		cout << "hit" << endl;
		selected = true;
	}
	else {
		cout << "miss" << endl;
		selected = false;
	}
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
