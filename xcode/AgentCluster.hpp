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
#include "CrowdAgent.h"

class AgentCluster {
    
private:
    std::vector<CrowdAgent*> agents;
    float radius;
    vec2 velocity, position;
    int i_levle; //level of iteration
    
public:
    void addAgent(CrowdAgent * agent);
    void calcRadius();
    void calcVelocity();
    void calcPosition();
};

#endif /* AgentCluster_hpp */
