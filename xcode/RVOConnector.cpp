//
//  RVOConnector.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-17.
//
//

#include "RVOConnector.hpp"
#include "Vector2.h"
#include "AGENT_CONST.h"

namespace RVOConn {
    
    // Default constructor
    RVOConnector::RVOConnector() {
        
        // Initialize RVO Sim
        sim = new RVO::RVOSimulator();
        
        // Initiate LR RVO Simulator
        LR_sim = new RVO::RVOSimulator();
        
        // Specify sim timestep
        sim->setTimeStep(0.25f);
        
        // Set LR sime timestep
        LR_sim->setTimeStep(0.25f);
        
        // Specify Sim default agent parameters
        sim->setAgentDefaults(200.0f, 10, 10.0f, 5.0f, 2.0f, 2.0f);
        LR_sim->setAgentDefaults(800.0f, 100, 10.0f, 5.0f, 2.0f, 2.0f);
        
    }
    
    // Constructor that integrates agent list in system with RVO2 lib system
    RVOConnector::RVOConnector(std::vector<CrowdAgent> * agents) : RVOConnector::RVOConnector() {
        
        // Set agent list reference in RVO connector to agent list referred in param.
        this->agents = agents;
        
        // Initialize RVO sim with agents in current system
        for(int i = 0; i < agents->size(); i++) {
            
            // Current position of agent
            vec2 pos   = (*agents)[i].getPos();
            
            // Current Velocity of agent
            vec2 vel   = (*agents)[i].getCurrentVelocity();
            
            // Adds the agent to the RVO sim
            sim->addAgent(RVO::Vector2(pos.x, pos.y));
            
            // Updates the radius of the agent
            sim->setAgentRadius(i, (*agents)[i].getRadius());
            
            // Updates the velocity of the agent
            sim->setAgentVelocity(i, RVO::Vector2(vel.x, vel.y));
            
            //Set Agent Preferred velocity
            sim->setAgentPrefVelocity(i, RVO::Vector2(vel.x, vel.y));
        }
    }
    
    void RVOConnector::updateRVO() {
        
        // Calculate RVO Velocities at base level at t_0
        std::vector<vec3> rvo_base = RVOCalc(8.0f);
        
        // Compute RVO look ahead velocities
        std::vector<vec3> rvo_lookahead = RVOLookAheadCalc();
        
        // Update agent's RVO
        updateRVOVelocities(&rvo_base, &rvo_lookahead);
        
    }
    
    std::vector<vec3> RVOConnector::RVOCalc(float r) {
        
        //Synchronize Values in RVO system with host system
        for(int i = 0; i < agents->size(); i++) {
            
            // Gets the current velocity
            vec2 vel = (*agents)[i].getCurrentVelocity();
            
            // gets the current agent position
            vec2 pos = (*agents)[i].getPos();
            
            // gets the radius of the agent
            float r  = (*agents)[i].getRadius();
            
            // Sets the agent's position
            sim->setAgentPosition(i, RVO::Vector2(pos.x, pos.y));
            
            //Set Agent Preferred velocity
            sim->setAgentPrefVelocity(i, RVO::Vector2(vel.x, vel.y));
            
            // Sets the agent's radius
            sim->setAgentRadius(i, r);
        }
        
        // Performs a step in the sim with updated/synced values
        sim->doStep();
        
        // Define the vector to return
        std::vector<vec3> RVO_Vel;
        
        // Generate return vector list
        for(int i = 0; i < sim->getNumAgents(); i++) {
            
            // Gets the RVO agent's velocity
            RVO::Vector2 v = sim->getAgentVelocity(i);
            
            // Pushes the velocity vector into RVO_Vel
            RVO_Vel.push_back( vec3(v.x(), v.y(), i) );
        }
        
        // Return Vector List
        return RVO_Vel;
    }
    
    // Calc RVO based on inputted positions
    std::vector<vec3> RVOConnector::RVOCalc(float r, std::vector<vec3> * pos) {
        
        // Sync values in RVO system with host system
        for(int i = 0; i < agents->size(); i++) {
            
            // Get current velocity of agent
            vec2 vel = (*agents)[i].getCurrentVelocity();
            
            // Set Agent Position in sim
            sim->setAgentPosition(i, RVO::Vector2((*pos)[i].x, (*pos)[i].y));
            
            // Set agent preferred velocity in sim
            sim->setAgentPrefVelocity(i, RVO::Vector2(vel.x, vel.y));
            
            // Set maximum velocity
            sim->setAgentMaxSpeed(i, AgentConst::MAX_AGENT_VEL_MAG);
            
            // Set agent radius in sim
            sim->setAgentRadius(i, r);
            
        }
        
        // Do simulation step
        sim->doStep();
        
        //Declare vector list to return
        std::vector<vec3> RVO_Vel;
        
        // Build RVO_Vel vector list
        for(int i = 0; i < sim->getNumAgents(); i++) {
            
            // Get Agent Velocity from sim
            RVO::Vector2 v = sim->getAgentVelocity(i);
            
            // Push velocity value into RVO_Vel
            RVO_Vel.push_back(vec3(v.x(), v.y(), i));
        }
        
        // Return RVO_Vel
        return RVO_Vel;
    }
    
    // Calculates RVO velocities for agents in agents with look ahead with max look ahead steps
    std::vector<vec3> RVOConnector::RVOLookAheadCalc() {
        
        // Iterate through each timestep
        for(int ts_i = 0; ts_i < AgentConst::MAX_LOOK_AHEAD_STEPS; ts_i++) {
        
            // Get Neighbors for each agent for each agent at timestep step_i
            for(int i = 0; i < agents->size(); i++) {
                
                // i is the current agent being eval (neighbor list being computad) with respect to agent n
                
                // Calculate the maximum radius an agent should be searching
                float r_max = AgentConst::AGENT_RADIUS + (2*AgentConst::MAX_AGENT_VEL_MAG)*(2^(AgentConst::MAX_LOOK_AHEAD_STEPS - 1));
                
                for(int n = 0; n < agents->size(); n++) {
                    
                    // Define the neighbor distance of agent[n] w.r.t. agent[i]
                    // Get extrapolated positions of agents wrt timestep
                    vec2 n_pos_ts_i = (*agents)[n].getPos() + ((float)ts_i)*(*agents)[n].getCurrentVelocity();
                    vec2 i_pos_ts_i = (*agents)[i].getPos() + ((float)ts_i)*(*agents)[i].getCurrentVelocity();
                    
                    // Get distance between the two
                    float agentDistance = length(n_pos_ts_i - i_pos_ts_i);
                    
                    // for each agent being checked, see if it is in the largest search radius, if not, then skip.
                    if(agentDistance <= r_max) {
                        
                        // Is the agent being evaluate the current agent?
                        if(&agents->at(i) != &agents->at(n)) {
                                
                            // Lower radius R+2v_max*dt_i-1
                            float r_lower = AgentConst::AGENT_RADIUS + (2*AgentConst::MAX_AGENT_VEL_MAG)*(2^(ts_i - 2));
                            
                            // Upper radius R+2v_max*dt_i
                            float r_upper = AgentConst::AGENT_RADIUS + (2*AgentConst::MAX_AGENT_VEL_MAG)*(2^(ts_i - 1));
                            
                            // Check to see if the agent is in this bound for this time ts_i
                            if( agentDistance >= r_lower && agentDistance <= r_upper) {
                                
                                // Add to appropriate row according to bound
                                (*agents)[i].addNeighbor(&(*agents)[n], ts_i);
                                
                                // Break the loop, evaluate the next neighbor
                                break;
                                
                                // if the agent being eval is the same as the current agent, then continue without adding to neighbor list for current
                            } else { continue; }
                            
                            // If the current agent is the agent that is being eval, then ignore and continue
                        } else { continue; }
                        
                        // If the agent falls outside max, then just continue onto the next agent
                    } else { continue; }
                    
                } // End iterating through other agents
                
                // Cluster Neighbor Agents in current ts_i timestep for current agent
                (*agents)[i].clusterNeighbors(ts_i);
                
                
            } // End get neighors
            
        
        } // END Iterating through each timestep
            
        
        
       
        
        // Cluster agents in each timestep for each neighborlist of each agent
        
    }
    
    // Updates the RVO Velocities
    void RVOConnector::updateRVOVelocities(std::vector<vec3> * v_rvoBase, std::vector<vec3> * v_rvoLR){
        
        // Iterate through the v_rvo vectorList
        for(int i = 0; i < agents->size(); i++) {
            
            // get velocity vector at 'i'
            float vx = ( (*v_rvoBase)[i].x + (*v_rvoLR)[i].x );
            float vy = ( (*v_rvoBase)[i].y + (*v_rvoLR)[i].y );
            
            // update the RVO velocity in agent i with v_rvo
            (*agents)[i].setRVO(vec2(vx, vy));
        }
    }
}




