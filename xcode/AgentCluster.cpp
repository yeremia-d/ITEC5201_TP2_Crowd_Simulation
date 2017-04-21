//
//  AgentCluster.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-19.
//
//

#include "AgentCluster.hpp"

// Cluster constructor
AgentCluster::AgentCluster(vec2 position, vec2 velocity, int ts_i){
    this->velocity.push_back(velocity);
    this->position.push_back(position);
    this->ts_i = ts_i;
}

// Adds agent to cluster
void AgentCluster::addAgent(vec2 position, vec2 velocity) {
    this->velocity.push_back(velocity);
    this->position.push_back(position);
}

// Returns true if cluster is at capacity
bool AgentCluster::isFull() {
    return velocity.size() > ts_i;
}

// Returns the position of the root agent
vec2 AgentCluster::getRootAgentPosition() {
    return position[0];
}

// Calculates the Radius of the cluster
void AgentCluster::calcRadius() {
    
    // Calc the cluster position. This should have been done, but just in case.
    calcPosition();
    
    // Declare and initialize distance of the farthest agent
    float maxRad = AgentConst::AGENT_RADIUS;
    
    // Find the farthest agent
    for(int i = 0; i < position.size(); i++) {
        float l = glm::length(cluster_position - position[i]);
        
        if(l > maxRad) { maxRad = l; }
    }
    
    // Compute the cluster radius
    cluster_radius = AgentConst::AGENT_RADIUS + maxRad*(ts_i);
}

// Compute the cluster position
void AgentCluster::calcPosition() {
    
    // initialize the sum
    vec2 sum = vec2();
    
    // Add all positions together
    for(int i = 0; i < position.size(); i++) { sum += position[i]; }
    
    // Divide sum by the number of agents (average)
    cluster_position = sum/(float)velocity.size();
}

// Compute the velocity of the cluster
void AgentCluster::calcVelocity() {
    
    // Initialize the sum of the velocities
    vec2 sum = vec2();
    
    // Sum the velocities
    for(int i = 0; i < velocity.size(); i++) { sum += velocity[i]; }
    
    // Divide by the number of agents
    cluster_velocity = sum/(float)velocity.size();
}

// Getter functions
vec2 AgentCluster::getClusterVelocity() { return cluster_velocity; }
vec2 AgentCluster::getClusterPosition() { return cluster_position; }
float AgentCluster::getClusterRadius()  { return cluster_radius;   }
