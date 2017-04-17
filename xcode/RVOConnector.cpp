//
//  RVOConnector.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-17.
//
//

#include "RVOConnector.hpp"
#include "RVO.h"

namespace RVOConn {
    std::vector<CrowdAgent> RVOConnector::getRVO(std::vector<CrowdAgent> agents) {
        std::vector<CrowdAgent> agentsToReturn = agents;
        
        RVO::RVOSimulator * sim = new RVO::RVOSimulator();
        
        // Set global timestep
        sim->setTimeStep(0.25f);
        
        // Setup Simulation
        sim->setAgentDefaults(150.0f, 10, 10.0f, 5.0f, 5.0f, 2.0f);
        
        // Add agents
        
        
        
        return agentsToReturn;
        
    }
}
