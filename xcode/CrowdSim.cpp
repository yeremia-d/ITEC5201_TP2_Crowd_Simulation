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
    AgentGroup g1 = AgentGroup(0, ci::Color(1,0,0));
    AgentGroup g2 = AgentGroup(1, ci::Color(0,1,0));
    
    // Initialize agent group 1
    for(int i = 100; i <= 300; i += 50 ) {
        for(int j = 100; j <= 550; j += 50) {
            g1.addAgent( CrowdAgent( vec2(i,j), vec2(i +100, j) ) );
        }
    }
    
    // Initialize agent group 2
    for(int k = 1000; k <= 1200; k += 50) {
        for(int l = 300; l <= 450; l += 50) {
            g2.addAgent( CrowdAgent(vec2(k, l), vec2(k, l)) );
        }
    }
    
    // push groups to the group stack
    agentGroups.push_back(g1);
    agentGroups.push_back(g2);
    
    // Build Agent List
    buildAgentList();
    
    // TODO: Only pushes one list in, need to do it for all
    agentGroups[0].setAgentList(&agentList);
    
}

// Update all groups
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

void CrowdSim::buildAgentList(){
    
    // TODO: Only pushes one list in, need to do it for all
    std::vector<CrowdAgent> a = * agentGroups[0].getAgents();
    
    for(int i = 0; i < a.size(); i++) {
        agentList.push_back(&a[i]);
    }
    
}
