//
//  VectorPoint.cpp
//  Fluids3D
//
//  Created by Michail Vanis on 19/03/2013.
//
//

#include "VectorPoint.h"

using namespace ci;

VectorPoint::VectorPoint() {
    
}

VectorPoint::VectorPoint(Vec3f location, Vec3f direction, float strength) {
    loc = location;
    dir = direction;
    str = strength;
    arrowLength = 5.0f;
    zoneLength = 0;
    headLength = 3.0f;
    headRadius = 3.0f;
}

void VectorPoint::update() {
    
}

void VectorPoint::draw() {
    gl::color(1.0f, 1.0f, 1.0f);
    gl::drawVector(loc, loc+dir * arrowLength, headLength, headRadius);
    gl::drawLine(loc, loc-dir * arrowLength);
}

void VectorPoint::setDirection(Vec3f direction) {
    dir = direction;
}