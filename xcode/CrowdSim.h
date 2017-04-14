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
#include "RVO.h"

class CrowdSim : public RVO::RVOSimulator {

public:
    void initBidirectionalSim();    // Initializes a bidirectional flow crowd simulation
    size_t addAgent(const RVO::Vector2 &originalPosition, const RVO::Vector2 &destinationPosition);
    void update();                  // Updates the Simulation (simulation and integration stage)
    void draw();                    // Draw agents in the simulation
};

#endif /* CrowdSim_hpp */
