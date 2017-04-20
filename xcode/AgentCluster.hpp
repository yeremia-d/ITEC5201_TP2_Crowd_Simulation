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

using namespace ci;

class AgentCluster {
    
private:
    float radius;
    std::vector<vec2> velocity, position;
    int ts_i; //level of iteration
    
public:
    AgentCluster(vec2 position, vec2 velocity, int ts_i);
    void addAgent(vec2 position, vec2 velocity);
    vec2 getRootAgentPosition();
    bool isFull();
    void calcRadius();
    void calcVelocity();
    void calcPosition();
};


#endif /* AgentCluster_hpp */
