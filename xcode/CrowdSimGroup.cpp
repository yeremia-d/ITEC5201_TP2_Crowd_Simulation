//
//  CrowdSimGroup.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdSimGroup.h"

AgentGroup::AgentGroup(int groupId)                         { this->groupId = groupId; size = 0; }

void AgentGroup::addAgent(CrowdAgent agent)                 {
    agents.push_back(agent);
    size++;
}

std::vector<CrowdAgent> AgentGroup::getAgents()             { return agents; }
void AgentGroup::update()                                   { for(int i = 0; i < size; i++) agents[i].update(); }
void AgentGroup::draw()                                     { for(int i = 0; i < size; i++) agents[i].draw(); }
