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
#include "CrowdAgent.h"
#include "RVOConnector.hpp"

class CrowdSim {

public:
    
    std::vector<CrowdAgent> agents; // List of Agents in the system
    RVOConn::RVOConnector RVO2Adaptor; // RVO System Adaptor
    
    CrowdSim();                     // Explicit Crowd Sim Constructor
    void initBidirectionalSim();    // Initializes a bidirectional flow crowd simulation
    void update();                  // Updates the Simulation (simulation and integration stage)
    void draw();                    // Draw agents in the simulation
};

#endif /* CrowdSim_hpp */
