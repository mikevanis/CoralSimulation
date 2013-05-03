#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "ParticleController.h"

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
    
    ParticleController controller;
    
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
};

void CoralSimulationApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(1280, 800);
    settings->setFrameRate(60.0f);
}

void CoralSimulationApp::setup() {
    controller = ParticleController(RESOLUTION);
    
    // CAMERA
    camDistance = 350.0f;
    eye = Vec3f(0.0f, 0.0f, camDistance);
    center = Vec3f::zero();
    up = Vec3f::yAxis();
    cam.setPerspective(75.0f, getWindowAspectRatio(), 5.0f, 5000.0f);
    
    // PARAMS
    mParams = params::InterfaceGl("Fluids 3D", Vec2i(200, 310));
    mParams.addParam("Scene rotation", &sceneRotation, "opened=1");
    mParams.addSeparator();
    mParams.addParam("Eye distance", &camDistance, "min=100.0 max=2000.0 step=50.0 keyIncr=s keyDecr=w");
    mParams.addSeparator();
    mParams.addButton("Load OBJ", bind(&ParticleController::loadOBJ, controller));
    mParams.addParam("Draw OBJ", &controller.drawOBJ);
    mParams.addSeparator();
    mParams.addParam("Draw vectors", &controller.drawVectors, "opened=1");
}

void CoralSimulationApp::mouseDown( MouseEvent event ) {
}

void CoralSimulationApp::update() {
    controller.update();
    eye = Vec3f(0.0f, 0.0f, camDistance);
    cam.lookAt(eye, center, up);
    gl::setMatrices(cam);
    gl::rotate(sceneRotation);
}

void CoralSimulationApp::draw() {
	gl::clear( Color( 0, 0, 0 ) );
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
    controller.draw();
    mParams.draw();
}

CINDER_APP_NATIVE( CoralSimulationApp, RendererGl )
