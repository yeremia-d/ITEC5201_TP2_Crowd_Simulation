//
//  CrowdSim.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdSim.h"
#include "CrowdAgent.h"
void CrowdSim::initBidirectionalSim() {
    setAgentDefaults(15.0f, 10, 10.0f, 5.0f, 5.0f, 2.0f);
    
    addAgent(RVO::Vector2(50,50), RVO::Vector2(0,0));
}

// Update all groups
void CrowdSim::update() {

}

// Draws the agents in the groups
void CrowdSim::draw() {
    
    for(int i = 0; i < agents_.size(); i++) {
        Vector2 v = getAgentPosition(i);
        float r = getAgentRadius(i);
        
        //gl::color(CA_Color);
        gl::drawSolidCircle(vec2(v.x(), v.y()), r);
        
    }
    
}

size_t CrowdSim::addAgent(const Vector2 &originalPosition, const Vector2 &destinationPosition)
{
    if (defaultAgent_ == NULL) { return RVO_ERROR; }
    
    CrowdAgent *agent = new CrowdAgent(dynamic_cast<RVOSimulator *>(this));
    
    agent->position_                = originalPosition;
    agent->CA_OriginalPosition      = originalPosition;
    agent->CA_DestinationPosition   = destinationPosition;
    agent->maxNeighbors_            = defaultAgent_->maxNeighbors_;
    agent->maxSpeed_                = defaultAgent_->maxSpeed_;
    agent->neighborDist_            = defaultAgent_->neighborDist_;
    agent->radius_                  = defaultAgent_->radius_;
    agent->timeHorizon_             = defaultAgent_->timeHorizon_;
    agent->timeHorizonObst_         = defaultAgent_->timeHorizonObst_;
    agent->velocity_                = defaultAgent_->velocity_;
    
    agent->id_                      = agents_.size();
    
    agents_.push_back(agent);
    
    return agents_.size() - 1;
}
