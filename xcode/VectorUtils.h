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

namespace VectorUtils {
    
    class VectorUtils {
    public:
        static ci::vec2 Add(ci::vec2 v1, ci::vec2 v2);   // Adds 2 vectors of type vec2
        static ci::vec3 Add(ci::vec3 v1, ci::vec3 v2);   // Adds 2 vectos of type vec3
        
        static ci::vec2 ScalarMult(ci::vec2 v, float s); // Multiplies a vector, of type vec2, with a scalar
        static ci::vec3 ScalarMult(ci::vec3 v, float s); // Multiplies a vector, of type vec3, with a scalar
        
        static float VectorMag(ci::vec2 v);
        static float VectorMag(ci::vec3 v);
        
        static ci::vec2 NormalizeVector(ci::vec2 v);
        static ci::vec3 NormalizeVector(ci::vec3 v);
    };

}

#endif /* VectorUtils_hpp */
