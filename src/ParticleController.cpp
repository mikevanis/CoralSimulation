//
//  ParticleController.cpp
//  Fluids3D
//
//  Created by Michail Vanis on 20/03/2013.
//
//

#include "ParticleController.h"

#define MAXPARTICLES 600

using namespace ci;
using std::list;
using namespace std;

ParticleController::ParticleController() {
    
}

ParticleController::ParticleController(int res) {
    // Get window width and height, and vector resolution
    
    resolution = res;
    width = app::getWindowWidth()/resolution;
    height = app::getWindowHeight()/resolution;
    depth = width;
    
    app::console() << "Width: " << width << std::endl;
    app::console() << "Height: " << height << std::endl;
    app::console() << "Depth: " << depth << std::endl;
    
    // Add vectors
    
    for(int z=0; z<depth; z++) {
        for(int y=0; y<height; y++) {
            for(int x=0; x<width; x++) {
                Vec3f location = Vec3f(x*resolution, y*resolution, z*resolution);
                Vec3f direction = Vec3f(0, 0, 1);
                VectorPoint newVector = VectorPoint(location, direction, 1.0f);
                newVector.zoneLength = resolution/2;
                vectorList.push_back(newVector);
            }
        }
    }
    /*
    test = VectorPoint(Vec3f(400, 400, 0), Vec3f(0, 1, 0), 1.0f);
    test2 = VectorPoint(Vec3f(400, 300, 200), Vec3f(0, 0, 1), 1.0f);
    vectorList.push_back(test);
    vectorList.push_back(test2);*/
}

void ParticleController::update() {
    
}

void ParticleController::draw(bool drawVectors, bool drawParticles) {
    gl::translate(Vec3f(width*resolution/2*-1, height*resolution/2*-1, width*resolution/2*-1));
    // Draw vectors
    if(drawVectors) {
        for(vector<VectorPoint>::iterator v = vectorList.begin(); v!=vectorList.end(); ++v) v->draw();
    }
}

// Add a single vector to the vector list.
void ParticleController::addVector(Vec3f location, Vec3f direction) {
    VectorPoint newVector = VectorPoint(location, direction, 1.0f);
    newVector.zoneLength = resolution/2;
    vectorList.push_back(newVector);
}

// Set the direction of all vectors in the vector list.
void ParticleController::setGeneralDirection(Vec3f direction) {
    for(vector<VectorPoint>::iterator v = vectorList.begin(); v!=vectorList.end(); ++v) {
        v->dir = direction;
    }
}

// Convert granularity to actual pixels
void ParticleController::applyResolution(Vec3f v, int res) {
    v.x = (v.x + 0.5f) * (float)res;
    v.y = (v.y + 0.5f) * (float)res;
    v.z = (v.z + 0.5f) * (float)res;
//    return v;
}