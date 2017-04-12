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

class CrowdSim {

//** Member Variables **//

private:
    static int              groupId_ITERATOR;    // Group ID Iterator
    std::vector<AgentGroup> agentGroups;


//** Member Functions **//

public:
    void initBidirectionalSim();    // Initializes the crowd simulation
    void update();                  // Updates the Simulation (simulation and integration stage)
    void draw();                    // Draw agents in the simulation
};

#endif /* CrowdSim_hpp */
