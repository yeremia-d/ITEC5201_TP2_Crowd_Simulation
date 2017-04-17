//
//  VectorUtils.hpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-10.
//
//

#ifndef VectorUtils_hpp
#define VectorUtils_hpp

#include <stdio.h>

using namespace ci;
namespace VectorUtils {
    
    class VectorUtils {
    public:
        static vec2 Add(vec2 v1, vec2 v2);   // Adds 2 vectors of type vec2
        static vec3 Add(vec3 v1, vec3 v2);   // Adds 2 vectos of type vec3
        
        static vec2 Subtract(vec2 v1, vec2 v2);
        static vec3 Subtract(vec3 v1, vec3 v2);
        
        static vec2 ScalarMult(vec2 v, float s); // Multiplies a vector, of type vec2, with a scalar
        static vec3 ScalarMult(vec3 v, float s); // Multiplies a vector, of type vec3, with a scalar
        
        static float VectorMag(vec2 v);
        static float VectorMag(vec3 v);
        
        static vec2 NormalizeVector(vec2 v);
        static vec3 NormalizeVector(vec3 v);
    };

}

#endif /* VectorUtils_hpp */
