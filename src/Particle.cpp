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
    acc = 0;
    vel = 8;
}

void Particle::update() {
    if(timer<=0) {
        if(prevLocations.size() == 1) isDead = true;
        else prevLocations.erase(prevLocations.begin());
    }
    else {
        //vel += 0.1;
        //vel *= (0.98 + acc);
        
        //if(vel<=0.05) loc += dir * 0.05;
        //else loc += dir * vel;
        
        //Vec3f randomDeviation = Vec3f(randFloat(-1, 1), randFloat(-1, 1), randFloat(-1, 1));
        //Vec3f deviated = dir*0.8 + randomDeviation*0.2;
        
        loc += dir * vel;
        
        timer -= 0.5f;
        
        prevLocations.push_back(loc);
        
        // Store point to point queue
        if(prevLocations.size() >= HISTORY) {
            prevLocations.erase(prevLocations.begin());
        }

    }
}

void Particle::draw() {
    gl::pushMatrices();
    gl::color(Color(1, 1, 1));
    gl::drawSphere(loc, radius * (timer/100));
    /*
    // Draw point array
    for(int i = 0; i < prevLocations.size()-1; i++) {
        gl::drawLine(prevLocations.at(i), prevLocations.at(i+1));
    }
    */
    gl::popMatrices();
}