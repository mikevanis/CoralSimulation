//
//  Quadrant.cpp
//  Fluids3D
//
//  Created by Michail Vanis on 19/03/2013.
//
//

#include "Quadrant.h"

#define DIRECTIONFRACTION 0.01f

using namespace ci;

Quadrant::Quadrant() {
    
}

Quadrant::Quadrant(VectorPoint *v[8]) {
    for(int i=0; i<8; i++) vectors[i] = v[i];
}

void Quadrant::draw() {
    
}
/*
bool Quadrant::isInQuadrant(Vec3f location) {
    
}
*/
Vec3f Quadrant::getAverageDirection(Vec3f location) {
    Vec3f dir[8];
    float dist[8];
    float totalDist;
    Vec3f averageDirection;
    
    for(int i=0; i<8; i++) {
        dir[i] = location - vectors[8]->loc;
        dist[i] = dir[i].lengthSquared();
        totalDist += dist[i];
    }
    for(int i=0; i<8; i++) {
        averageDirection += vectors[i]->dir*(1-dist[i]/totalDist);
    }
    
    averageDirection.safeNormalize();
    return averageDirection;
}