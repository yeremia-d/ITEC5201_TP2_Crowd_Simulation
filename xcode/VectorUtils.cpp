//
//  VectorUtils.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-10.
//
//

#include "VectorUtils.h"
#include "math.h"


namespace VectorUtils {
    using namespace ci;
    vec2 VectorUtils::Add(vec2 v1, vec2 v2)         { return vec2(v1.x + v2.x, v1.y + v2.y);              }
    vec3 VectorUtils::Add(vec3 v1, vec3 v2)         { return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }
    
    vec2 VectorUtils::ScalarMult(vec2 v, float s)   { return vec2(v.x * s, v.y * s);                      }
    vec3 VectorUtils::ScalarMult(vec3 v, float s)   { return vec3(v.x * s, v.y * s, v.z * s);             }
    
    float VectorUtils::VectorMag(vec2 v)            { return sqrt(powf(v.x, 2) + powf(v.y, 2));                }
    float VectorUtils::VectorMag(vec3 v)            { return sqrt(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2)); }
    
    vec2 VectorUtils::NormalizeVector(vec2 v)       { return ScalarMult(v, VectorMag(v)); }
    vec3 VectorUtils::NormalizeVector(vec3 v)       { return ScalarMult(v, VectorMag(v)); }
}

