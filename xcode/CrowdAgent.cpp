//
//  CrowdAgent.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdAgent.h"
#include "AGENT_CONST.h"

using namespace ci;

// Crowd Agent Default Constructor
CrowdAgent::CrowdAgent() {
    this->acc           = vec2();
    this->vel_current   = vec2();
    this->position_o    = vec2();
    this->position_t    = vec2();
    this->color         = Color(1,1,1);
    this->id            = 0;
    
    // Initiate Cluster List
    for(int i = 0; i < AgentConst::MAX_LOOK_AHEAD_STEPS; i++) clusters.push_back(std::vector<AgentCluster>());
    
}

// Crowd Agent Constructor
CrowdAgent::CrowdAgent(vec2 position_o, vec2 position_t) : CrowdAgent::CrowdAgent() {
    this->position_o = position_o;
    this->position_t = position_t;
    this->position_c = position_o;
}

// Sets Agent Color
void CrowdAgent::setColor(Color color)  { this->color = color; }
void CrowdAgent::setRVO(vec2 v)         { this->vel_RVO = v;   }
void CrowdAgent::setId(size_t id)       { this->id = id;       }

// Adds a neighbor at a specific ts_i
void CrowdAgent::addNeighbor(CrowdAgent * agent) { neighbors.push_back(agent); }

// Getters
vec2    CrowdAgent::getPos()             { return position_c;               }
vec2    CrowdAgent::getCurrentVelocity() { return vel_current;              }
float   CrowdAgent::getRadius()          { return AgentConst::AGENT_RADIUS; }
Color   CrowdAgent::getColor()           { return color;                    }


// Crowd Agent Update Loop
void CrowdAgent::update() {
    
    // Solve forces
    vec2 forces = solveForces();
    
    // Integration
    acc           = glm::normalize(forceToAcceleration(forces));
    vel_current   = ((15.0f * vel_RVO) + acc * 0.05f) * 3.0f;
    
    vec2 vel_c_n = glm::normalize(vel_current);
    
    float m = glm::length(vel_current);
    float mC = glm::clamp(m, 0.0f, AgentConst::MAX_AGENT_VEL_MAG);
    
    position_c   += mC*vel_c_n / ci::app::getFrameRate();
}

// Computes the acceleration of an agent based on the applied forces and mass
vec2 CrowdAgent::forceToAcceleration(vec2 f) { return f/AgentConst::AGENT_MASS; }

// Force Solvers
vec2 CrowdAgent::solveForces() {
    // Driving Force to Destination
    vec2 f_d = solveTargetForce();
    
    // Sum forces
    vec2 f_sum = f_d;
    
    // Return the summed forces to be integrated
    return f_sum;
}

// Solves for force that drives agent to target
vec2 CrowdAgent::solveTargetForce() {
    return position_t - position_c;
}

// Gets the distance between this agent and the agent provided in the parameter
float CrowdAgent::getDistance(CrowdAgent *agent) {
    vec2 diff = this->getPos() - agent->getPos();
    return glm::length(diff);
}

void CrowdAgent::clusterNeighbors(int ts_i) {
    
    // Iterate through all neighbors
    while(neighbors.size() > 0) {
        
        // Tage a neighbor
        CrowdAgent a = *neighbors.back();
        
        // Set clusterfound flag to false
        bool clusterFound = false;
        
        // if there are clusters at this timeframe
        if(clusters[ts_i].size() > 0) {

            // iterate through cluster to see if there is a cluster that a can join
            for(int i = 0; i < clusters[ts_i].size(); i++) {
                
                // If the cluster is full, continue
                if(clusters[ts_i].at(i).isFull()) {continue;}
                
                // If the agent in question is further than the max separation, continue
                if(glm::length(clusters[ts_i].at(i).getRootAgentPosition() - a.getPos()) > RVOConnConst::CLUSTER_MAX_AGENT_SEPARATION) { continue; }
                
                // Else, if agent eval can go into cluster and is within max separation, add to cluster
                else {
                    
                    // Add agent to cluster
                    clusters[ts_i].at(i).addAgent(a.getPos(), a.getCurrentVelocity());
                    
                    // set cluster found flag to true
                    clusterFound = true;
                    
                    // remove agent from neighbors
                    neighbors.pop_back();
                    
                    //break loop
                    break;
                }
            }
        }
        
        // If no cluster is found or no clusters in this timeframe, create a new cluster
        if(!clusterFound || clusters[ts_i].size() == 0) {
            
            // Create new cluster
            AgentCluster c = AgentCluster(a.getPos(), a.getCurrentVelocity(), ts_i);
            
            // Push cluster into cluster list
            clusters[ts_i].push_back(c);
            
            // remove agent from neighbor list
            neighbors.pop_back(); // remove agent entry from neighbors list
        }
    }
    
    // Once all neighbors are processed, then clear the neighbor list (house cleaning)
    neighbors.clear();
}

// Calculate cluster attributes
void CrowdAgent::solveClusterAttributes() {
    for(int ts_i = 0; ts_i < clusters.size(); ts_i++) {
        for(int i = 0; i < clusters[ts_i].size(); i++) {
            clusters[ts_i].at(i).calcPosition();
            clusters[ts_i].at(i).calcRadius();
            clusters[ts_i].at(i).calcVelocity();
        }
    }
}

std::vector<std::vector<AgentCluster>> * CrowdAgent::getClusters() {
    return &clusters;
}





