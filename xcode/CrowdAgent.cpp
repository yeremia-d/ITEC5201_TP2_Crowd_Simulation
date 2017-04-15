//
//  CrowdAgent.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdAgent.h"
#include "RVO.h"

using namespace ci;

CrowdAgent::CrowdAgent(RVOSimulator *sim) : RVO::Agent(sim) {
    this->CA_Mass                   = 1.0f;
    this->CA_Color                  = Color(1,1,1);
}

void CrowdAgent::setColor(Color color) { this->CA_Color = color;} // Sets Agent Color

void CrowdAgent::update() {
    // get neighbors
    
    
    velocity_ += prefVelocity_ + newVelocity_;
    // Solve forces
    position_ += velocity_ * 0.005;
    // Integration
    
}




// Computes the acceleration of an agent based on the applied forces and mass
Vector2 CrowdAgent::forceToAcceleration(Vector2 f) { return f/CA_Mass; }


// Force Solvers
Vector2 CrowdAgent::solveForces() {
    // Driving Force to Destination
    
    // calc collision
    
    // if collision occurs
    // conservation of momentum
    
    // recalculate new path based on density grid
    
    // perform RVO Long-Range LCA
    
    // perform RVO LCA
    
    // calc pushing force
    
    // calc friction force
    
    // calc social forces
    
    // Sum forces
    Vector2 f_sum = Vector2();
    
    // Return the summed forces to be integrated
    return f_sum;
}

Vector2 CrowdAgent::solveTargetForce() {
    Vector2 targetForce = Vector2();
    
    return targetForce;
}



