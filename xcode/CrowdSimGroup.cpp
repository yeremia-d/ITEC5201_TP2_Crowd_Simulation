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

std::vector<CrowdAgent> * AgentGroup::getAgents() {
    return &agents;
}

void AgentGroup::setAgentList(std::vector<CrowdAgent*> * agentList) {
    this->agentList = agentList;
}

// Update all agents in this group
void AgentGroup::update() {
    
    // Loop through agents in this group
    for(int i = 0; i < size; i++) {
        
        // Call to Update the neighnors by passing current agent list
        agents[i].updateNeighbors(agentList);
        
        // Update agent position by performing force calculations.
        agents[i].update();
    }
}

void AgentGroup::draw() {
    for(int i = 0; i < size; i++) {
        agents[i].draw();
    }
}

int AgentGroup::getSize() {
    return size;
}
