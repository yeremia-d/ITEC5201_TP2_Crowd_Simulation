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
    for(int i = 50; i < 300; i +=25)
        for(int j = 100; j < 600; j +=25) {
            agents.push_back(CrowdAgent(vec2(i,j), vec2(i+100, j+100)));
        }
}

// Update Agents positions
void CrowdSim::update() {
}

// Draws the agents in the groups
void CrowdSim::draw() {
    
    // Clears Canvas
    gl::clear();
    
    // Draws Agents
    for(int i = 0; i < agents.size(); i++) {
        gl::color(agents[i].getColor());
        gl::drawSolidCircle(agents[i].getPos(), agents[i].getRadius());
    }
}



/*
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
 */
