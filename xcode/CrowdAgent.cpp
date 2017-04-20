//
//  CrowdAgent.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdAgent.h"
#include "AGENT_CONST.h"

using namespace ci;

// Crowd Agent Default Constructor
CrowdAgent::CrowdAgent() {
    this->acc           = vec2();
    this->vel_current   = vec2();
    this->position_o    = vec2();
    this->position_t    = vec2();
    this->color         = Color(1,1,1);
    this->id            = 0;
    
    // Initiate neighbors list
    
    for(int init_it = 0; init_it < AgentConst::MAX_LOOK_AHEAD_STEPS; init_it++) {
        neighbors.push_back(std::vector<CrowdAgent *>());
    }
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

void CrowdAgent::addNeighbor(CrowdAgent * agent, int i) { neighbors[i].push_back(agent); }

// Getters
vec2    CrowdAgent::getPos()            { return position_c; }
float   CrowdAgent::getRadius()         { return AgentConst::AGENT_RADIUS; }
Color   CrowdAgent::getColor()          { return color; }
vec2    CrowdAgent::getCurrentVelocity(){ return vel_current; }

std::vector<std::vector<CrowdAgent *>> * CrowdAgent::getNeighbors() { return &neighbors; }

// Crowd Agent Update Loop
void CrowdAgent::update() {
    
    // Solve forces
    vec2 forces = solveForces();
    
    // Integration
    acc           = forceToAcceleration(forces);
    vel_current   = ((15.0f * vel_RVO) + acc * 0.05f) * 3.0f;
    position_c   += vel_current / ci::app::getFrameRate();
}

// Computes the acceleration of an agent based on the applied forces and mass
vec2 CrowdAgent::forceToAcceleration(vec2 f) {
    return f/AgentConst::AGENT_MASS;
}

// Force Solvers
vec2 CrowdAgent::solveForces() {
    // Driving Force to Destination
    vec2 f_d = solveTargetForce();
    
    // RVO/LR-RVO Velocity (take it in as a velocity)
    vec2 f_r = vel_RVO;
    
    // Solve for social forces
    vec2 f_s = solveSocialForce();
    
    // Sum forces
    vec2 f_sum = f_d + f_r + f_s;
    
    // Return the summed forces to be integrated
    return f_sum;
}

// Solves for force that drives agent to target
vec2 CrowdAgent::solveTargetForce() {
    return position_t - position_c;
}

vec2 CrowdAgent::solveSocialForce() {
    vec2 socialForce = vec2();
    
    return socialForce;

}

float CrowdAgent::weighting(int weightFunction) {
    
    switch(weightFunction) {
        case WeightingFnDefn::TARGET_FORCE:
            return 1;
            break;
        default: return 1;
            break;
    }
}

float CrowdAgent::getDistance(CrowdAgent *agent) {
    vec2 diff = this->getPos() - agent->getPos();
    return glm::length(diff);
}




