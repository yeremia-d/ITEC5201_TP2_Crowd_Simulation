//
//  AgentCluster.hpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-19.
//
//

#ifndef AgentCluster_hpp
#define AgentCluster_hpp

#include <stdio.h>
#include "AGENT_CONST.h"

using namespace ci;

class AgentCluster {
    
private:
    float   cluster_radius;         // Agent Cluster Radius
    
    vec2    cluster_velocity,       // Computed Agent Velocity
            cluster_position;       // Computed Agent Position
    
    std::vector<vec2>   velocity,   // Velocity list of agents in cluster
                        position;   // Position list of agents in the cluster
    
    int ts_i;                       // Level of iteration
    
public:
    
    // Agent Cluster Constructor
    AgentCluster(vec2 position, vec2 velocity, int ts_i);
    
    // Adds an agent to the cluster
    void addAgent(vec2 position, vec2 velocity);
    
    // Returns if the cluster is at capacity
    bool isFull();
    
    // Calculates the cluster's radius
    void calcRadius();
    
    // Calculates the cluster's velocity
    void calcVelocity();
    
    // Calculates the cluster's position
    void calcPosition();
    
    // gets the position of the first agent
    vec2 getRootAgentPosition();
    
    // Returns the cluster's velocity
    vec2 getClusterVelocity();
    
    // Returns the cluster's position
    vec2 getClusterPosition();
    
    // Returns the cluster's radius
    float getClusterRadius();
    
};


#endif /* AgentCluster_hpp */
