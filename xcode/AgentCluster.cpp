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

void AgentCluster::calcRadius() {
    
    calcPosition();
    
    float maxRad = AgentConst::AGENT_RADIUS;
    
    for(int i = 0; i < position.size(); i++) {
        float l = glm::length(cluster_position - position[i]);
        
        if(l > maxRad) { maxRad = l; }
    }
    
    cluster_radius = 2*AgentConst::AGENT_RADIUS + maxRad;
}

void AgentCluster::calcPosition() {
    vec2 sum = vec2();
    
    for(int i = 0; i < position.size(); i++) { sum += position[i]; }
    
    cluster_position = sum/(float)velocity.size();
}

void AgentCluster::calcVelocity() {
    vec2 sum = vec2();
    
    for(int i = 0; i < velocity.size(); i++) { sum += velocity[i]; }
    
    cluster_velocity = sum/(float)velocity.size();
    
    
}

vec2 AgentCluster::getClusterVelocity() { return cluster_velocity; }
vec2 AgentCluster::getClusterPosition() { return cluster_position; }
float AgentCluster::getClusterRadius() { return cluster_radius; }
