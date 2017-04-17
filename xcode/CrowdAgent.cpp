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
    
    
    // Solve forces
    
    
    Vector2 forces = solveForces();
    
    // Integration
    CA_Acceleration = forceToAcceleration(forces);
    
    velocity_ = 0.25*CA_Acceleration + 10 * newVelocity_;
    position_ += velocity_ * (1 / ci::app::getFrameRate());
    
}

// Computes the acceleration of an agent based on the applied forces and mass
Vector2 CrowdAgent::forceToAcceleration(Vector2 f) { return f/CA_Mass; }


// Force Solvers
Vector2 CrowdAgent::solveForces() {
    // Driving Force to Destination
    Vector2 f_destination = normalize(CA_DestinationPosition - position_);
    
    // calc collision
    Vector2 f_c;
    
    // if collision occurs
    // conservation of momentum
    Vector2 f_m;
    
    // calc pushing force
    Vector2 f_p;
    
    // calc friction force
    Vector2 f_f;
    
    // calc social forces
    
    
    // Sum forces
    Vector2 f_sum = f_destination;
    
    // Return the summed forces to be integrated
    return f_sum;
}

Vector2 CrowdAgent::solveTargetForce() {
    Vector2 targetForce = Vector2();
    
    return targetForce;
}

