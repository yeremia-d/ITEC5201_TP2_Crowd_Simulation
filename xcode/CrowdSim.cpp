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
    
    // initialize agent groups
    AgentGroup g1 = AgentGroup(0);
    AgentGroup g2 = AgentGroup(1);
    
    // Initialize agent group 1
    g1.addAgent( CrowdAgent(vec2(100, 100), vec2(100, 0)) );
    
    // Initialize agent group 2
   
    
    // push groups to the group stack
    agentGroups.push_back(g1);
    agentGroups.push_back(g2);
    
}

void CrowdSim::update() {
    for(int i = 0; i < agentGroups.size(); i++) {
        agentGroups[i].update();
    }
}

void CrowdSim::draw() {
    for(int i = 0; i < agentGroups.size(); i++) {
        agentGroups[i].draw();
    }
}
