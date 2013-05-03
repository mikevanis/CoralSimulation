//
//  VectorPoint.h
//  Fluids3D
//
//  Created by Michail Vanis on 19/03/2013.
//
//

#ifndef Fluids3D_VectorPoint_h
#define Fluids3D_VectorPoint_h

#pragma once
#include "cinder/Vector.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include <vector>

class VectorPoint {
public:
    VectorPoint();
    VectorPoint(ci::Vec3f location, ci::Vec3f direction, float strength);
    void update();
    void draw();
    void setDirection(ci::Vec3f direction);

    ci::Vec3f loc;
    ci::Vec3f dir;
    float str;
    float arrowLength, headLength, headRadius, zoneLength;
};

#endif
