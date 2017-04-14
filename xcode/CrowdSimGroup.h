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
    
    std::vector<CrowdAgent*> * agentList;
    
    
public:
    
    AgentGroup(int groupId, ci::Color agentColor);
    
    void setAgentList(std::vector<CrowdAgent *> * agentList);
    
    
    void addAgent(CrowdAgent agent);
    
    int getSize();
    
    std::vector<CrowdAgent> * getAgents();
    
    void update();
    
    void draw();
};
