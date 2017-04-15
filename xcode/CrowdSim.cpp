//
//  CrowdSim.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdSim.h"
#include "CrowdAgent.h"
#include "KdTree.h"

void CrowdSim::initBidirectionalSim() {
    
    setAgentDefaults(150.0f, 10, 10.0f, 5.0f, 5.0f, 2.0f);
    
    for(int i = 50; i < 300; i +=25)
        for(int j = 100; j < 600; j +=25) {
            size_t id = addAgent(RVO::Vector2(i,j), RVO::Vector2(0,0));
            setAgentPrefVelocity(id, Vector2(rand() % 10 + 1, rand() % 1));
        }
    

}

// Update Agents positions
void CrowdSim::update() {
    
    kdTree_->buildAgentTree();
    
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (int i = 0; i < static_cast<int>(agents_.size()); ++i) {
        agents_[i]->computeNeighbors();
        agents_[i]->computeNewVelocity();
    }
    
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (int i = 0; i < static_cast<int>(agents_.size()); ++i) {
        static_cast<CrowdAgent *>(agents_[i])->update();
    }
    
    globalTime_ += timeStep_;
    
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
