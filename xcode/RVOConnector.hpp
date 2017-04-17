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
        static std::vector<CrowdAgent> getRVO(std::vector<CrowdAgent> agents);
    };
}


#endif /* RVOConnector_hpp */

