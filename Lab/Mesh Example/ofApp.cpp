#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cam.setDistance(30.0);
	cam.lookAt(glm::vec3(0, 0, 0));
	ofSetBackgroundColor(ofColor::black);

	// hardcode test triangle
	//
	mesh.verts.push_back(glm::vec3(10, 0, 0));
	mesh.verts.push_back(glm::vec3(15, 0, 0));
	mesh.verts.push_back(glm::vec3(10, 5, 0));
    mesh.verts.push_back(glm::vec3(15, 5, 0));
    
    mesh.verts.push_back(glm::vec3(10, 0, 10));
    mesh.verts.push_back(glm::vec3(15, 0, 10));
    mesh.verts.push_back(glm::vec3(10, 5, 10));
    mesh.verts.push_back(glm::vec3(15, 5, 10));

   
	mesh.triangles.push_back(Triangle(0, 1, 2));
    mesh.triangles.push_back(Triangle(1, 2, 3));
    mesh.triangles.push_back(Triangle(4, 5, 6));
    mesh.triangles.push_back(Triangle(5, 6, 7));
    
    mesh.triangles.push_back(Triangle(0, 1, 2));
    mesh.triangles.push_back(Triangle(1, 2, 3));
    mesh.triangles.push_back(Triangle(4, 5, 6));
    mesh.triangles.push_back(Triangle(5, 6, 7));
    
    mesh.triangles.push_back(Triangle(3, 7, 8));
    mesh.triangles.push_back(Triangle(3, 4, 8));
    mesh.triangles.push_back(Triangle(1, 2, 5));
    mesh.triangles.push_back(Triangle(2, 5, 6));
    
    
     
}

void ofApp::objOpener() {
    ifstream myFile("monster-light-triangles-no-uvs.obj.obj"); //finds file
    //exits if there isn't a file
    if(!myFile.is_open()) {
        cout << "File cannot open" << endl;
        return 0;
    } else {
        cout << "File open" << endl;
    }
    
    /*
    string line;
    while(getline(myFile, line)) {
        cout << line << endl;
    }
     */
          
    //variables
    string vORf;
    string myStringX, myStringY, myStringZ;
    string line;
    int counterV;
    int counterF;
    int x2, y2, z2;
    float x, y, z;

    while(getline(myFile, line)){
        //skips blank lines or lines with comments
        if (line.length() == 0 || line[0] == '#') continue;
        
        //assigns each part of the line into the variables
        stringstream ss(line);
        getline(ss, vORf, ' ');
        getline(ss, myStringX, ' ');
        getline(ss, myStringY, ' ');
        getline(ss, myStringZ, ' ');
            
        //if about vertices
        if(vORf.compare("v") == 0) {
            counterV++;
            x = stof(myStringX);
            y = stof(myStringY);
            z = stof(myStringZ);
            mesh.verts.push_back(glm::vec3(x,y,z));
        }
            
        //if about faces
        if(vORf.compare("f") == 0) {
            counterF++;
            x2 = stoi(myStringX);
            y2 = stoi(myStringY);
            z2 = stoi(myStringZ);
            mesh.triangles.push_back(Triangle(x2, y2, z2));
        }
    }
    
    //Draws all the triangles and vertexes
    for (int i = 0; i < mesh.triangles.size(); i++) {
            ofDrawTriangle(mesh.verts[mesh.triangles[i].vertInd[0]], mesh.verts[mesh.triangles[i].vertInd[1]], mesh.verts[mesh.triangles[i].vertInd[2]]);
    }
        
    //Information about the model
    cout << "Number of Vertices " << counterV << endl;
    cout << "Number of Faces " << counterF << endl;
    cout << "Size of Mesh in KB " << (mesh.triangles.size() * counterF) + (mesh.verts.size() * counterV) << endl;
     
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
    objOpener();
//	ofDrawGrid();
//	ofSetColor(0, 255, 0);  // red, green, blue components for RGB space

	// encapsulate this code in a "drawAxis()" method.
	//
	ofSetColor(ofColor::green);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 5.0, 0));
	ofSetColor(ofColor::red);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(5.0, 0, 0));
	ofSetColor(ofColor::blue);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 0, 5.0));


	// connectivity 
	//
	ofSetColor(ofColor::white);
	ofNoFill();
    
    for (int i = 0; i < mesh.triangles.size(); i++) {
            ofDrawTriangle(mesh.verts[mesh.triangles[i].vertInd[0]], mesh.verts[mesh.triangles[i].vertInd[1]], mesh.verts[mesh.triangles[i].vertInd[2]]);
    }
    
     
	cam.end();
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
