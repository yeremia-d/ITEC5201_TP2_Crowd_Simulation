//
//  Integrator.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "Integrator.h"

vec2 Integrator::LeapFrog(vec2 acc, vec2 vel, vec2 pos) {
    vec2 nextPos = vec2();
    
    return nextPos;
}

// 2nd Order Runge-Kutta
vec2 Integrator::RungeKutta2(vec2 acc, vec2 vel, vec2 pos) {
    vec2 nextPos = vec2();
    
    return nextPos;
}

// 4th Order Runge-Kutta
vec2 Integrator::RungeKutta4(vec2 dVal, vec2 initVal, int subStep) {
    vec2 output = vec2();
    vec2 k1, k2, k3, k4;
    
    return output;
}

// Explicit Euler Method
vec2 Integrator::ExpEuler(vec2 dVal, vec2 initVal, int subStep) {
    
    vec2 output = vec2();
    
    output.x = initVal.x + dVal.x/subStep;
    output.y = initVal.y + dVal.y/subStep;
    
    return output;
}
