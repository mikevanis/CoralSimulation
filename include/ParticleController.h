//
//  ParticleController.h
//  Fluids3D
//
//  Created by Michail Vanis on 20/03/2013.
//
//

#ifndef CoralSimulation_ParticleController_h
#define CoralSimulation_ParticleController_h

#pragma once
#include "Particle.h"
#include "VectorPoint.h"
#include "Quadrant.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "cinder/ImageIo.h"
#include "cinder/Rand.h"
#include <list>
#include <vector>
#include <fstream>
#include <math.h>

class ParticleController {
public:
    ParticleController();
    ParticleController(int res);
    
    // Particle system
    void update();
    void draw();
    void applyQuadrantForces();
    void addParticle(ci::Vec3f location);
    void addVector(ci::Vec3f location, ci::Vec3f direction);
    void removeParticles(int amt);
    void createQuadrantsFromVectors();
    void setGeneralDirection(ci::Vec3f direction);
    void applyGeneralForce();
    
    // Vector search and manipulation
    VectorPoint* getVectorOnLocation(ci::Vec3f &position);
//    ci::Vec3f applyResolution(ci::Vec3f v, int res);
    void applyResolution(ci::Vec3f v, int res);
    VectorPoint* currentVector;
    VectorPoint generalDirection;
    
    // Data structures
    std::list<Particle> particleList;
    std::vector<VectorPoint> vectorList;
    std::list<Quadrant> quadrantList;
    
    bool drawVectors;
    bool drawParticles;
    bool drawOBJ;
    
    // Control vars
    int resolution;
    bool autoParticles = false;
    int width, height, depth;
    
    VectorPoint test;
    VectorPoint test2;
};

#endif
