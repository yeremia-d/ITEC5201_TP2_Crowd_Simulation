//
//  CrowdAgent.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdAgent.h"

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
    this->id            = 0;
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
void CrowdAgent::setId(size_t id)       { this->id = id; }

// Getters
vec2    CrowdAgent::getPos()            { return position_c; }
float   CrowdAgent::getRadius()         { return radius; }
Color   CrowdAgent::getColor()          { return color; }
vec2    CrowdAgent::getCurrentVelocity(){ return vel_current; }

// Crowd Agent Update Loop
void CrowdAgent::update() {
    
    // Solve forces
    vec2 forces = solveForces();
    
    // Integration
    acc           = forceToAcceleration(forces);
    vel_current   = ((15.0f * vel_RVO) + acc * 0.05f) * 3.0f;
    position_c   += vel_current * (1 / ci::app::getFrameRate());
}

// Computes the acceleration of an agent based on the applied forces and mass
vec2 CrowdAgent::forceToAcceleration(vec2 f) {
    return f/mass;
}

// Force Solvers
vec2 CrowdAgent::solveForces() {
    // Driving Force to Destination
    vec2 f_destination = solveTargetForce();
    
    // calc collision
    
    
    // if collision occurs
    // conservation of momentum
    vec2 f_m;
    
    // calc pushing force
    vec2 f_p;
    
    // RVO/LR-RVO Velocity (take it in as a velocity)
    vec2 f_r = vel_RVO;
    
    // calc friction force
    vec2 f_f;
    
    // calc social forces
    
    
    // Sum forces
    vec2 f_sum = f_destination + f_r;
    
    // Return the summed forces to be integrated
    return f_sum;
}

// Solves for force that drives agent to target
vec2 CrowdAgent::solveTargetForce() {
    vec2 f_t = position_t - position_c;
    return f_t;
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

