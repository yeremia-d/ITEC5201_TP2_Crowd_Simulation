//
//  CrowdSimGroup.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdSimGroup.h"

AgentGroup::AgentGroup(int groupId, ci::Color agentColor) {
    this->groupId       = groupId;
    this->agentColor    = agentColor;
    size                = 0;
}

void AgentGroup::addAgent(CrowdAgent agent) {
    
    // Sets agent color of current group
    agent.setColor(agentColor);
    
    // Push agent to linked list data struct
    agents.push_back(agent);
    
    // Update size of the group
    size++;
}

std::vector<CrowdAgent> AgentGroup::getAgents() {
    return agents;
}

void AgentGroup::update() {
    for(int i = 0; i < size; i++) {
        agents[i].update();
    }
}

void AgentGroup::draw() {
    for(int i = 0; i < size; i++) {
        agents[i].draw();
    }
}
