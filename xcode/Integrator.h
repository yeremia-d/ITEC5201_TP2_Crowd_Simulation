//
//  Integrator.hpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#ifndef Integrator_hpp
#define Integrator_hpp

#include <stdio.h>

using namespace ci;

// Integration Service that takes in an initial position, vel, acc and returns a new position

class Integrator {
    
public:
    
    // Leapfrog Integration Method
    vec2 LeapFrog(vec2 acc, vec2 vel, vec2 pos);
    
    // 2nd Order Runge-Kutta
    vec2 RungeKutta2(vec2 acc, vec2 vel, vec2 pos);
    
    // 4th Order Runge-Kutta
    vec2 RungeKutta4(vec2 dVal, vec2 initVal, int subStep);
    
    // Explicit Euler Method
    vec2 ExpEuler(vec2 dVal, vec2 initVal, int subStep);
    
};

#endif /* Integrator_hpp */

