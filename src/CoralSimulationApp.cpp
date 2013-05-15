#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "ParticleController.h"
#include "MeshController.h"


#define RESOLUTION 100

using namespace ci;
using namespace ci::app;
using namespace std;

class CoralSimulationApp : public AppNative {
  public:
    void prepareSettings(Settings *settings);
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void saveImage();
    
    ParticleController controller;
    MeshController coral;
    
    Surface screenshot;
    
    // PARAMS
    params::InterfaceGl mParams;
    
    // CAMERA
    CameraPersp  cam;
    Quatf sceneRotation;
    Vec3f eye, center, up;
    float camDistance;
    
    // BOOLS
    bool drawVectors;
    bool drawParticles;
    bool takePicture;
};

void CoralSimulationApp::prepareSettings(Settings *settings) {
    
    settings->enableHighDensityDisplay();
    settings->setWindowSize(1280, 800);
    settings->setFrameRate(60.0f);
}

void CoralSimulationApp::setup() {
    
    controller = ParticleController(RESOLUTION);
    
    coral = MeshController("Donation.obj");
    coral.targetScale = 100.0f;
    coral.prevScale = 100.0f;
    coral.update();
    
    // CAMERA
    camDistance = 350.0f;
    eye = Vec3f(0.0f, 0.0f, camDistance);
    center = Vec3f::zero();
    up = Vec3f::yAxis();
    cam.setPerspective(75.0f, getWindowAspectRatio(), 5.0f, 5000.0f);
    
    // PARAMS
    mParams = params::InterfaceGl("Coral Simulation", Vec2i(400, 500));
    mParams.addParam("Scene rotation", &sceneRotation, "opened=1");
    mParams.addSeparator();
    mParams.addParam("Eye distance", &camDistance, "min=100.0 max=2000.0 step=50.0 keyIncr=s keyDecr=w");
    mParams.addSeparator();
    mParams.addText("Mesh drawing");
    mParams.addParam("Draw wireframe", &coral.drawWireframe);
    mParams.addParam("Draw normals", &coral.drawNormals);
    mParams.addParam("Mesh scaling", &coral.targetScale, "min=1.0 max=200.0 step=1.0");
    mParams.addSeparator();
    mParams.addText("Particle system");
    mParams.addParam("Draw vectors", &controller.drawVectors, "opened=1");
    mParams.addParam("Throw particles", &controller.autoParticles);
    mParams.addSeparator();
    mParams.addButton("Take picture", bind(&CoralSimulationApp::saveImage, this));
    
}

void CoralSimulationApp::mouseDown( MouseEvent event ) {
}

void CoralSimulationApp::update() {
    
    controller.update();
    coral.update();
    
    eye = Vec3f(0.0f, 0.0f, camDistance);
    cam.lookAt(eye, center, up);
    gl::setMatrices(cam);
    gl::rotate(sceneRotation);
}

void CoralSimulationApp::draw() {
	gl::clear( Color( 0, 0, 0 ) );
    gl::enableDepthRead();
    gl::enableDepthWrite();
    glDisable( GL_CULL_FACE );
    
    controller.draw();
    coral.draw();
    
    gl::drawCoordinateFrame(40.0f, 6.0f, 3.0f);
    
    // SNAPSHOT
    if(takePicture) {
        screenshot = copyWindowSurface();
        fs::path imgPath = getSaveFilePath("screenshot.jpg");
        if(!imgPath.empty()) writeImage(imgPath, screenshot);
        takePicture = false;
    }
    
    mParams.draw();
}

void CoralSimulationApp::saveImage() {
    takePicture = true;
}

CINDER_APP_NATIVE( CoralSimulationApp, RendererGl )
