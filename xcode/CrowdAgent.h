//
//  CrowdAgent.hpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#ifndef CrowdAgent_hpp
#define CrowdAgent_hpp

#include <stdio.h>

#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "VectorUtils.h"

#include "Agent.h"
#include "RVOSimulator.h"
#include "CrowdSim.h"


using namespace ci;
using namespace RVO;

class CrowdAgent : public Agent {
    
public:
    
    Vector2 CA_Acceleration;        // Acceleration
    Vector2 CA_OriginalPosition;    // Starting position
    Vector2 CA_DestinationPosition; // Agent Destination
    
    float CA_Mass;                  // Agent Mass
    float CA_MaxAcceleration;       // Maximum Acceleration
    
    Color CA_Color;                 // Agent Color
    

    CrowdAgent(RVOSimulator * sim);
    
    // Setters
    void setColor(Color color);
    
    // Getters
    Vector2 getPos();
    Vector2 getCurrentVelocity();
    Vector2 getPreferredVelocity();
    Vector2 getAcc();
    
    // Perform integration (acc->vel->pos)
    void update();
    

    // Solves all forces (repulsive and attractive)
    Vector2 solvePushingForce();
    Vector2 solveFrictiongForce();
    Vector2 solveSocialForce();
    Vector2 solveLRLCAForce();
    
    Vector2 solveTargetForce();    // Returns normalized vector towards the agent's target
    
    Vector2 solveForces();
    
    // Converts a Force to Acceleration based on agent's mass
    Vector2 forceToAcceleration(Vector2 f);
    
    
};

#endif /* CrowdAgent_hpp */
