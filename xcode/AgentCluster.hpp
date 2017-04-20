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
    float cluster_radius;
    vec2 cluster_velocity, cluster_position;
    std::vector<vec2> velocity, position;
    int ts_i; //level of iteration
    
public:
    AgentCluster(vec2 position, vec2 velocity, int ts_i);
    
    void addAgent(vec2 position, vec2 velocity);
    bool isFull();
    void calcRadius();
    void calcVelocity();
    void calcPosition();
    
    vec2 getRootAgentPosition(); // gets the position of the first agent
    vec2 getClusterVelocity();
    vec2 getClusterPosition();
    
    float getClusterRadius();
    
    
    
};


#endif /* AgentCluster_hpp */
