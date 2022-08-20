#include "ofApp.h"
//@author Andy Luong
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor::white);
    //ofSetBackgroundColor(ofColor::black)
    ofSetVerticalSync(true); //60 fps
    
    cam.setDistance(30.0); //makes preset triangles and .obj same size
    
    /* If not using the hardCodedDraw function
    //8 Hard coded vertices by inputing positions
    mesh.verts.push_back(glm::vec3(10, 0, 0));
    mesh.verts.push_back(glm::vec3(15, 0, 0));
    mesh.verts.push_back(glm::vec3(10, 5, 0));
    mesh.verts.push_back(glm::vec3(15, 5, 0));
    
    mesh.verts.push_back(glm::vec3(10, 0, 10));
    mesh.verts.push_back(glm::vec3(15, 0, 10));
    mesh.verts.push_back(glm::vec3(10, 5, 10));
    mesh.verts.push_back(glm::vec3(15, 5, 10));
 
   //8 Hard coded triangles by connecting vertices
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
     */
}
 
//--------------------------------------------------------------
void ofApp::update(){
 
}
 
//Alternative method for reading a .obj
void ofApp::objOpener() {
    ifstream myFile("monster-light-triangles-no-uvs.obj.obj"); //finds file
    
    //exits if there isn't a file
    if(!myFile.is_open()) {
        cout << "File cannot open" << endl;
        return 0;
    } else {
        cout << "File open" << endl;
    }
    
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
void ofApp::draw(){
    cam.begin(); //camera window
    
    //Allows Drag and Drop
    ofEnableDepthTest();
    this->light.enable();
    this->camera.begin();
    this->drawFunction();
    this->camera.end();
    this->light.disable();
    ofDisableDepthTest();
    //or objOpener();
    
    
    //Displays the X, Y, Z Axis
    ofSetColor(ofColor::green);
    ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 5.0, 0));
    ofSetColor(ofColor::red);
    ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(5.0, 0, 0));
    ofSetColor(ofColor::blue);
    ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 0, 5.0));
    ofSetColor(ofColor::green);
    ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 5.0, 0));
    ofSetColor(ofColor::red);
    ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(5.0, 0, 0));
    ofSetColor(ofColor::blue);
    ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 0, 5.0));
    
    // /* */ if using .obj file
    //Draws all the hard codedtrianlges into the window
    for (int i = 0; i < mesh.triangles.size(); i++) {
            ofDrawTriangle(mesh.verts[mesh.triangles[i].vertInd[0]], mesh.verts[mesh.triangles[i].vertInd[1]], mesh.verts[mesh.triangles[i].vertInd[2]]);
    }
    
    //To make object transparent
    ofSetColor(ofColor::white);
    ofNoFill();
    
    //Part 1: Enable the following line and disable Part 2 and press f
    //hardCodedDraw();
    
    //Part 2: Enable the following line and disable Part 1 and drag and drop
    stats();
    
    //Extra: If both enabled = pressing f gives error, if both disabled = no harded coded draw or stats, only drag and drop
    
    cam.end(); //Camera finishes
}
 
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //Displays the Hard Coded Mesh if .obj not loaded
    switch (key) {
        case 'f':
              this->changeDrawFunction(&ofxAssimpModelLoader::drawFaces);
              break;
    }
}

void ofApp::hardCodedDraw() {
    //Draws all the triangles and vertexes
    mesh.verts.push_back(glm::vec3(10, 0, 0));
    mesh.verts.push_back(glm::vec3(15, 0, 0));
    mesh.verts.push_back(glm::vec3(10, 5, 0));
    mesh.verts.push_back(glm::vec3(15, 5, 0));
    
    mesh.verts.push_back(glm::vec3(10, 0, 10));
    mesh.verts.push_back(glm::vec3(15, 0, 10));
    mesh.verts.push_back(glm::vec3(10, 5, 10));
    mesh.verts.push_back(glm::vec3(15, 5, 10));
 
   //8 Hard coded triangles by connecting vertices
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

void ofApp::stats() {
stringstream ss;
int numVertices = model.getMesh(0).getNumVertices();
int numFaces = model.getMesh(0).getUniqueFaces().size();
int sizeVertices = sizeof(model.getMesh(0).getVertices());
int sizeFaces = sizeVertices * 3;

ss << "Number of Vertices: " << ofToString(numVertices) << " Number of Faces: " << ofToString(numFaces) << " Size of Mesh in KB " << ofToString(sizeVertices + sizeFaces) << endl;
ofDrawBitmapString(ss.str().c_str(), 20, 20);
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
//Drag and Drop method for reading a obj file
void ofApp::dragEvent(ofDragInfo dragInfo){
    ofClear(255, 255, 255);
    this->model.loadModel(dragInfo.files[0], 20);
    this->changeDrawFunction(&ofxAssimpModelLoader::drawWireframe);
}
 
//Switches to the another object when drag and drop to an existing one
void ofApp::changeDrawFunction(std::function<void(ofxAssimpModelLoader)> func) {
    this->drawFunction = std::bind(func, this->model);
}
