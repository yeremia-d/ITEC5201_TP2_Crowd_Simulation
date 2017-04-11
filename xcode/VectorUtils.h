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

namespace VectorOps {
    
    class VectorUtils {
    public:
        vec2 Add(vec2 v1, vec2 v2); // Adds 2 vectors of type vec2
        vec3 Add(vec3 v1, vec3 v2); // Adds 2 vectos of type vec3
        
        vec2 ScalarMult(vec2 v, float s); // Multiplies a vector, of type vec2, with a scalar
        vec3 ScalarMult(vec3 v, float s); // Multiplies a vector, of type vec3, with a scalar
    };

}

#endif /* VectorUtils_hpp */
