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
        RVO::RVOSimulator * sim;            // Referenced variable to RVO simulator
        std::vector<CrowdAgent> * agents;   // Referenced variable to list of agents
        
        std::vector<std::vector<vec3>> LR_pos;  // Lookahead Position [timestep - i][array of positions each corresponding to an agent]
        
        // Default Constructor
        RVOConnector();
        
        // Constructor that connects the agent list to this adaptor
        RVOConnector(std::vector<CrowdAgent> * agents);
        
        // Updates RVO Velocities (including Long Range) of all agents in list
        void updateRVO();
        
        // Calculates the RVO for agents at a specific i level (spec by radius r) and returns a vec3 [x, y, uid]. (Base case formula)
        std::vector<vec3> RVOCalc(float r);
        
        // Calculates RVO for a
        std::vector<vec3> RVOCalc(float r, std::vector<vec3> * pos);
        
        // Calculates RVO with Lookahead for agents
        std::vector<vec3> RVOLookAheadCalc();
        
        // Updates the RVO velocities in agent lists with velocities in parameter
        void updateRVOVelocities(std::vector<vec3> * v_rvo);
        

        
    };
}


#endif /* RVOConnector_hpp */

