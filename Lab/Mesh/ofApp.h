#pragma once
//Headers for Drag and Drop
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include <functional>
#include "ofMain.h"
//@author Andy Luong
 
//Triangle has indices
class Triangle {
public:
    Triangle(int i1, int i2, int i3) { vertInd[0] = i1, vertInd[1] = i2, vertInd[2] = i3; }
    int vertInd[3];
};
 
//A messh has vertices and triangles
class Mesh {
public:
    vector<glm::vec3> verts;
    vector<Triangle> triangles;
};
 
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
    void objOpener(); //Open .obj via fopen
    void hardCodedDraw();
    void stats();
    ofEasyCam cam;
    Mesh mesh;
 
//Drag and Drop variables
private:
    ofxAssimpModelLoader model;
    ofLight light;
    ofEasyCam camera;
    float cameraOrbit;
    std::function<void()> drawFunction;
 
    void changeDrawFunction(std::function<void(ofxAssimpModelLoader)> func);
};
