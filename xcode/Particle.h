//
//  Particle.h
//  Fluids3D
//
//  Created by Michail Vanis on 15/03/2013.
//
//

#ifndef Fluids3D_Particle_h
#define Fluids3D_Particle_h

#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Util.h"
#include <vector>

class Particle {
public:
    Particle();
    Particle(ci::Vec3f location, ci::Vec3f direction);
    void update();
    void draw();
    
    ci::Vec3f loc;
    ci::Vec3f dir;
    float vel;
    float acc;
    float timer;
    float radius;
    bool isDead = false;
    int currentStep;
    
    std::vector<ci::Vec3f> prevLocations;
};


#endif
