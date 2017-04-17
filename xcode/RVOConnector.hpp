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

namespace RVOConn {
    class RVOConnector {
    public:
        static std::vector<CrowdAgent> getRVO(std::vector<CrowdAgent> agents); // Takes in all agents in the system and returns their specific RVO
    };
}


#endif /* RVOConnector_hpp */

