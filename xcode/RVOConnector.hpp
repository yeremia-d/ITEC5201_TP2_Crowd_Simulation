//
//  RVOConnector.hpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-17.
//
//

#ifndef RVOConnector_hpp
#define RVOConnector_hpp

#include <stdio.h>
#include "CrowdAgent.h"
#include "RVO.h"

namespace RVOConn {
    class RVOConnector {
    public:
        RVO::RVOSimulator * sim;
        std::vector<CrowdAgent> * agents;
        
        RVOConnector(); // Default Constructor
        RVOConnector(std::vector<CrowdAgent> * agents);
        void updateRVO(); // Updates RVO Velocities (including Long Range) of all agents in list
        std::vector<vec3> RVOCalc(float r);   // Calculates the RVO for agents at a specific i level (spec by radius r) and returns a vec3 [x, y, uid]
        void updateRVOVelocities(std::vector<vec3> * v_rvo); // Updates the RVO velocities in agent lists with velocities in parameter
        
    };
}


#endif /* RVOConnector_hpp */

