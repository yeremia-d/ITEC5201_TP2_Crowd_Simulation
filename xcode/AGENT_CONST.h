//
//  AGENT_CONST.h
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-18.
//
//

#ifndef AGENT_CONST_h
#define AGENT_CONST_h

// Agent Constants
namespace AgentConst {
    const int   MAX_LOOK_AHEAD_STEPS    = 15;        // Maximum number of lookahead steps
    const float MAX_AGENT_VEL_MAG       = 10.0f;    // Maximum velocity magnitude for agent
    const float MAX_AGENT_ACC_MAG       = 10.0f;    // Maximum acceleration magnitude for agent
    const float AGENT_MASS              = 1.0f;     // Agent Mass
    const float AGENT_RADIUS            = 5.0f;     // Agent Radius
}

// Weighting Function Definition for specifiers
namespace WeightingFnDefn {
    const int   TARGET_FORCE            = 0;        // Weighting Function
}


namespace RVOConnConst {
    const float CLUSTER_MAX_AGENT_SEPARATION = 25.0f;
}
#endif /* AGENT_CONST_h */

