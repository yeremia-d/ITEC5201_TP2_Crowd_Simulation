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

class CrowdAgent {
    
private:
    vec2 pos;          // Position
    
    vec2 cVel;         // Current Velocity
    vec2 pVel;         // Preferred Velocity
    
    vec2 acc;          // Acceleration
    
    vec2 orig_pos;     // Starting position
    vec2 dest_pos;     // Agent Destination
    
    float radius;      // Radius of Agent
    
    float mass;        // Agent Mass
    
    
public:
    
    // Default Constructor
    CrowdAgent();
    
    // Constructor with Radius specified (static agent)
    CrowdAgent(float radius);
    
    // Constructor with Radius and originating and destination
    CrowdAgent(float radius, vec2 orig_pos, vec2 dest_pos);
    
    // Constructor with Default Radius but Originating and destination positions specified
    CrowdAgent(vec2 orig_pos, vec2 dest_pos);
    
    // Setters
    void setPos(vec2 pos);
    void setCurrentVelocity(vec2 cVel);
    void setPreferredVelocity(vec2 pVel);
    void setAcc(vec2 acc);
    
    // Getters
    vec2 getPos();
    vec2 getCurrentVelocity();
    vec2 getPreferredVelocity();
    vec2 getAcc();
    
    // Perform integration (acc->vel->pos)
    void update();
    
    // Draw Agent
    void draw();
    
    // Updates Neighbors
    void updateNeighbors();
    
private:
    // Solves all forces (repulsive and attractive)
    vec2 solveForces();
    
};

#endif /* CrowdAgent_hpp */
