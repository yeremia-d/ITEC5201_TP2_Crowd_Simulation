//
//  CrowdAgent.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdAgent.h"
#include "VectorUtils.h"

using namespace ci;

// Crowd Agent Default Constructor
CrowdAgent::CrowdAgent() {
    this->acc           = vec2();
    this->acc_max       = 1.0f;
    this->vel_pref      = vec2();
    this->vel_current   = vec2();
    this->position_o    = vec2();
    this->position_t    = vec2();
    this->mass          = 1.0f;
    this->color         = Color(1,1,1);
    this->radius        = 5.0f;
}

// Crowd Agent Constructor
CrowdAgent::CrowdAgent(vec2 position_o, vec2 position_t) : CrowdAgent::CrowdAgent() {
    this->position_o = position_o;
    this->position_t = position_t;
    this->position_c = position_o;
}

// Sets Agent Color
void CrowdAgent::setColor(Color color)  { this->color = color; }
void CrowdAgent::setRVO(vec2 v)         { this->vel_RVO = v; }

// Getters
vec2    CrowdAgent::getPos()            { return position_c; }
float   CrowdAgent::getRadius()         { return radius; }
Color   CrowdAgent::getColor()          { return color; }

// Crowd Agent Update Loop
void CrowdAgent::update() {
    
    // Solve forces
    vec2 forces = solveForces();
    
    // Integration
    acc         += forceToAcceleration(forces);
    vel_current  = vel_RVO + acc;
    position_c  += vel_current * (1 / ci::app::getFrameRate());
}

// Computes the acceleration of an agent based on the applied forces and mass
vec2 CrowdAgent::forceToAcceleration(vec2 f) {
    return VectorUtils::VectorUtils::ScalarMult(f, 1/mass);
}

// Force Solvers
vec2 CrowdAgent::solveForces() {
    // Driving Force to Destination
    vec2 f_destination = solveTargetForce();
    
    // calc collision
    vec2 f_c;
    
    // if collision occurs
    // conservation of momentum
    vec2 f_m;
    
    // calc pushing force
    vec2 f_p;
    
    // calc friction force
    vec2 f_f;
    
    // calc social forces
    
    
    // Sum forces
    vec2 f_sum = f_destination;
    
    // Return the summed forces to be integrated
    return f_sum;
}

// Solves for force that drives agent to target (normalized)
vec2 CrowdAgent::solveTargetForce() {
    vec2 f_t = VectorUtils::VectorUtils::Subtract(position_t, position_c);
    return VectorUtils::VectorUtils::NormalizeVector(f_t);;
}

float CrowdAgent::weighting(int weightFunction) {
    
    switch(weightFunction) {
        case TARGETFORCE:
            return 1;
            break;
        default: return 1;
            break;
    }
}

