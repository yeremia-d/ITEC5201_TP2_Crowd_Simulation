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
