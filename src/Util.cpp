//
//  Util.cpp
//  Fluids3D
//
//  Created by Michail Vanis on 15/03/2013.
//
//

#include "Util.h"

Util::Util() {
    
}

// Range mapping function (ported from Arduino) ----------------------------
float Util::mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min;
}

// Range mapping function (ported from Arduino) ----------------------------
int Util::mapValue(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min;
}