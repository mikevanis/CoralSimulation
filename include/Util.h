//
//  Util.h
//  Fluids3D
//
//  Created by Michail Vanis on 15/03/2013.
//
//

#ifndef Fluids3D_Util_h
#define Fluids3D_Util_h

class Util {
public:
    Util();
    float mapValue(float x, float in_min, float in_max, float out_min, float out_max);
    int mapValue(int x, int in_min, int in_max, int out_min, int out_max);
};

#endif
