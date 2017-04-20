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

class AgentCluster {
    
private:
    float radius;
    ci::vec2 velocity, position;
    int ts_i; //level of iteration
    
public:
    void calcRadius();
    void calcVelocity();
    void calcPosition();
};


#endif /* AgentCluster_hpp */
