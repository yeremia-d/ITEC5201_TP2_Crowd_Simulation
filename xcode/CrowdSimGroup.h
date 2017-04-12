//
//  CrowdSimGroup.hpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#ifndef CrowdSimGroup_hpp
#define CrowdSimGroup_hpp

#include <stdio.h>
#include <vector>

#include "CrowdAgent.h"

#endif /* CrowdSimGroup_hpp */

class AgentGroup {

private:
    int groupId;
    int size;
    ci::Color agentColor;
    std::vector<CrowdAgent> agents;
    
    
public:
    
    AgentGroup(int groupId, ci::Color agentColor);
    
    void addAgent(CrowdAgent agent);
    
    std::vector<CrowdAgent> getAgents();
    
    void update();
    
    void draw();
};
