//
//  AgentCluster.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-19.
//
//

#include "AgentCluster.hpp"

AgentCluster::AgentCluster(vec2 position, vec2 velocity, int ts_i){
    this->velocity.push_back(velocity);
    this->position.push_back(position);
    this->ts_i = ts_i;
}

void AgentCluster::addAgent(vec2 position, vec2 velocity) {
    this->velocity.push_back(velocity);
    this->position.push_back(position);
}

bool AgentCluster::isFull() {
    return velocity.size() > ts_i;
}

vec2 AgentCluster::getRootAgentPosition() {
    return position[0];
}
