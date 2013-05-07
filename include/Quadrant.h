//
//  Quadrant.h
//  Fluids3D
//
//  Created by Michail Vanis on 19/03/2013.
//
//

#ifndef CoralSimulation_Quadrant_h
#define CoralSimulation_Quadrant_h

#pragma once
#include "cinder/Vector.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "VectorPoint.h"

class Quadrant {
public:
    Quadrant();
    Quadrant(VectorPoint *v[8]);
    void draw();
    bool isInQuadrant(ci::Vec3f location);
    ci::Vec3f getAverageDirection(ci::Vec3f location);
    
    VectorPoint *vectors[8];
};

#endif
