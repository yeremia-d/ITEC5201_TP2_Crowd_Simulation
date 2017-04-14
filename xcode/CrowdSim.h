//
//  CrowdSim.hpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#ifndef CrowdSim_hpp
#define CrowdSim_hpp

#include <stdio.h>
#include <vector>
#include "CrowdSimGroup.h"
#include "CrowdAgent.h"

class CrowdSim {

//** Member Variables **//

private:
    static int              groupId_ITERATOR;    // Group ID Iterator
    std::vector<AgentGroup> agentGroups;         // List of agent groups
    std::vector<CrowdAgent *> agentList;

//** Member Functions **//

public:
    void initBidirectionalSim();    // Initializes a bidirectional flow crowd simulation
    void buildAgentList();          // Builds the list of agents
    void update();                  // Updates the Simulation (simulation and integration stage)
    void draw();                    // Draw agents in the simulation
};

#endif /* CrowdSim_hpp */
