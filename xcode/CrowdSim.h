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

class CrowdSim {

//** Member Variables **//

private:
static int groupId_ITERATOR;    // Group ID Iterator


//** Member Functions **//

public:
void init();                    // Initializes the crowd simulation
void addGroup();                // Adds group of agents to the crowd simulation
void addGroup(int numAgents);   // Adds new group with a specified number of agents
void update();                  // Updates the Simulation (simulation and integration stage)
};

#endif /* CrowdSim_hpp */
