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

using namespace ci;

// Declaring Constants
const int TARGETFORCE = 0; // Weighting Function

class CrowdAgent {
    
private:
    
    // Class Members
    vec2  acc;          // Acceleration
    float acc_max;      // Maximum Acceleration
    
    vec2 vel_pref;      // Preferred Velocity
    vec2 vel_current;   // Current Velocity
    vec2 vel_RVO;       // RVO velocity that is solved in the sim
    
    vec2 position_o;    // Starting position
    vec2 position_t;    // Agent Destination (Target)
    vec2 position_c;    // Current Position
    
    float mass;         // Agent Mass
    float radius;       // Agent Circle Radius
    
    Color color;        // Agent Color
    
    size_t id;          // Agent ID
    
public:
    
    // Constructors
    CrowdAgent();                                   // Default
    CrowdAgent(vec2 position_o, vec2 position_t);   // With defined start and target positions
    
    // Setters
    void setColor(Color color);
    void setRVO(vec2 v);
    void setId(size_t id);
    
    // Getters
    vec2 getPos();
    float getRadius();
    Color getColor();
    vec2 getCurrentVelocity();
    vec2 getPreferredVelocity();
    vec2 getAcc();
    
    // Perform integration (acc->vel->pos)
    void update();
    

    // Solves all forces (repulsive and attractive)
    vec2 solveForces();
    
    vec2 solvePushingForce();
    vec2 solveFrictiongForce();
    vec2 solveSocialForce();
    
    // Returns normalized vector towards the agent's target
    vec2 solveTargetForce();
    
    // Converts a Force to Acceleration based on agent's mass
    vec2 forceToAcceleration(vec2 f);
    
    // Weighting Functions
    float weighting(int weightFunction);
};

#endif /* CrowdAgent_hpp */
