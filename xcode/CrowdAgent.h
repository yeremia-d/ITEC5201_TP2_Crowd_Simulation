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

#include "AgentCluster.hpp"

using namespace ci;



class CrowdAgent {
    
private:
    
    // Class Members
    vec2 acc;                       // Acceleration
    vec2 vel_current;               // Current Velocity
    vec2 vel_RVO;                   // RVO velocity that is solved in the sim
    vec2 force_collision;           // Collision Force when checking for collisions
    vec2 position_o;                // Starting position
    vec2 position_t;                // Agent Destination (Target)
    vec2 position_c;                // Current Position
    
    Color color;                    // Agent Color
    
    std::vector<vec2> vel_RVOLR;    // Long Range RVO
    
    std::vector<CrowdAgent *> neighbors; // Neighbors of Crowd agent for LR RVO
    
    std::vector<std::vector<AgentCluster>> clusters; // Clusters of agents
    
    size_t id;                      // Agent ID
    
    int AgentMaxLookaheadSteps;     // Agent max look ahead steps after curtailing
    
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
    vec2 getAcc();
    
    // Add Neighbor at row i
    void addNeighbor(CrowdAgent * agent);
    
    // Returns the neighbor List
    std::vector<std::vector<CrowdAgent *>> * getNeighbors();
    
    // Returns the clusters
    std::vector<std::vector<AgentCluster>> * getClusters();
    
    // Perform integration (acc->vel->pos)
    void update();
    
    // Solves all forces (repulsive and attractive)
    vec2 solveForces();
    
    // Solve for social forces
    vec2 solveSocialForce();
    
    // Returns normalized vector towards the agent's target
    vec2 solveTargetForce();
    
    // Converts a Force to Acceleration based on agent's mass
    vec2 forceToAcceleration(vec2 f);
    
    // Computes Curtailing Function
    void updateLRCurtail();
    
    // Weighting Functions
    float weighting(int weightFunction);
    
    // returns the distance between this agent and a given agent
    float getDistance(CrowdAgent * agent);
    
    // Clusters neighbors in a given timestep ts_i
    void clusterNeighbors(int ts_i);
    
    void solveClusterAttributes();
};

#endif /* CrowdAgent_hpp */
