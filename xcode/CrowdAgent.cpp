//
//  CrowdAgent.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdAgent.h"

using namespace ci;

CrowdAgent::CrowdAgent(){
    this->pos       = vec2();
    this->cVel      = vec2();
    this->pVel      = vec2();
    this->acc       = vec2();
    this->orig_pos  = vec2();
    this->dest_pos  = vec2();
    this->radius    = 10.0f;
    this->mass      = 10.0f;
}

CrowdAgent::CrowdAgent(float radius) : CrowdAgent() {
    this->radius = radius;
}

CrowdAgent::CrowdAgent(float radius, vec2 orig_pos, vec2 dest_pos) : CrowdAgent() {
    this->radius    = radius;
    this->orig_pos  = orig_pos;
    this->dest_pos  = dest_pos;
}

CrowdAgent::CrowdAgent(vec2 orig_pos, vec2 dest_pos) : CrowdAgent() {
    this->orig_pos  = orig_pos;
    this->dest_pos  = dest_pos;
}

void CrowdAgent::update() {
    // get neighbors
    
    // calc collision
    
        // if collision occurs
            // conservation of momentum
    
            // recalculate new path based on density grid
    
    // perform RVO Long-Range LCA
    
    // perform RVO LCA
    
    // calc pushing force
    
    // calc friction force
    
    // calc social forces
    
    // sum forces
    vec2 totalForces = vec2();
    
    // Integration
    vec2 accleration = forceToAcceleration(totalForces);                    // get acceleration
    vec2 velocity    = VectorUtils::VectorUtils::Add(cVel, accleration);    // Integrate acceleration for new velocity
    vec2 newPosition = VectorUtils::VectorUtils::Add(pos, velocity);        // integrate velocity for new position
    
    // Update Agent's Values
    acc     = accleration;  // set current acceleration
    cVel    = velocity;     // set current agent velocity
    pos     = newPosition;  // set current position to new position
}

// Agent Draw Function
void CrowdAgent::draw() {
    gl::drawSolidCircle(pos, radius);
}

// Class Setters
void CrowdAgent::setPos(vec2 pos)                { this->pos   = pos;  }
void CrowdAgent::setCurrentVelocity(vec2 cVel)   { this->cVel  = cVel; }
void CrowdAgent::setPreferredVelocity(vec2 pVel) { this->pVel  = pVel; }
void CrowdAgent::setAcc(vec2 acc)                { this->acc   = acc;  }

// Class Getters
vec2 CrowdAgent::getPos()               { return pos;  }
vec2 CrowdAgent::getCurrentVelocity()   { return cVel; }
vec2 CrowdAgent::getPreferredVelocity() { return pVel; }
vec2 CrowdAgent::getAcc()               { return acc;  }


// Computes the acceleration of an agent based on the applied forces and mass
vec2 CrowdAgent::forceToAcceleration(vec2 f) { return VectorUtils::VectorUtils::ScalarMult(f, 1/mass); }

// Force Solvers


