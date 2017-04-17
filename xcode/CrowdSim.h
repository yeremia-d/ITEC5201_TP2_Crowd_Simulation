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
    
    std::vector<CrowdAgent> agents;         // List of Agents in the system
    RVOConn::RVOConnector RVO2Adaptor;      // RVO System Adaptor
    
    // Explicit Crowd Sim Constructor
    CrowdSim();
    
    // Initializes a bidirectional flow crowd simulation
    void initBidirectionalSim();
    
    // Updates the Simulation (simulation and integration stage)
    void update();
    
    // Draw agents in the simulation
    void draw();
};

#endif /* CrowdSim_hpp */
