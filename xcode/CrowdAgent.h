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
    vec2    acc,               // Acceleration
            vel_current,       // Current Velocity
            vel_RVO,           // RVO velocity that is solved in the sim
            position_o,        // Starting position
            position_t,        // Agent Destination (Target)
            position_c;        // Current Position
    
    Color   color;             // Agent Color
    
    size_t  id;                // Agent ID
    
    std::vector<CrowdAgent *> neighbors;                // Neighbors of Crowd agent for LR RVO
    std::vector<std::vector<AgentCluster>> clusters;    // Clusters of agents
    
public:
    
    // Default Constructor
    CrowdAgent();
    
    // With defined start and target positions
    CrowdAgent(vec2 position_o, vec2 position_t);
    
    // Setters
    void setColor(Color color);
    void setRVO(vec2 v);
    void setId(size_t id);
    
    // Getters
    vec2 getPos();
    vec2 getCurrentVelocity();
    vec2 getAcc();
    float getRadius();
    Color getColor();
    
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
    
    // Solves attributes for clusters
    void solveClusterAttributes();
};

#endif /* CrowdAgent_hpp */
