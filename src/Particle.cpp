//
//  Particle.cpp
//  Fluids3D
//
//  Created by Michail Vanis on 15/03/2013.
//
//
#include "Particle.h"

using namespace ci;
using namespace std;

#define HISTORY 50
#define RADIUS 3.0f
#define LIFE 350
#define FRICTION 0.98f

Particle::Particle() {
    
}

// Predetermined location and direction
Particle::Particle(Vec3f location, Vec3f direction) {
    loc = location;
    dir = direction;
    radius = RADIUS;
    timer = LIFE;
}

void Particle::update() {
    if(timer<=0) {
        if(prevLocations.size() == 1) isDead = true;
        else prevLocations.erase(prevLocations.begin());
    }
    else {
        
    }
}

void Particle::draw() {
    
}