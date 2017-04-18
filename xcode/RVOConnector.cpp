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
        
        // Specify sim timestep
        sim->setTimeStep(0.25f);
        
        // Specify Sim default agent parameters
        sim->setAgentDefaults(300.0f, 100, 10.0f, 5.0f, 2.0f, 2.0f);
        
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
        updateRVOVelocities(&rvo_base);
        
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
    
    // Calculates RVO velocities for agents in agents with look ahead with max look ahead steps
    std::vector<vec3> RVOConnector::RVOLookAheadCalc() {
        // "update" all agent positions based on v_current, generate positions for each time steps to a max of MAX_TIMESTEP
            // at each timestep, integrate based on velocity to get positions - create a fn that takes in agents, and returns std::vector<vec3> with [x,y,uid]
        // compute RVO for all (due to library)
        
        // Update curtailing factor on all agents based on velocity
            // update curtailing fn that updates max num of iterations based on current vel of agent
        
        // iterate through each time step,
            // on each iteration, iterate through agents. if i <= iMax for specific agents, then apply RVO with agent radius adjusted for the timestep, if not, continue
        
        
    }
    
    // Updates the RVO Velocities
    void RVOConnector::updateRVOVelocities(std::vector<vec3> * v_rvo){
        
        // Iterate through the v_rvo vectorList
        for(int i = 0; i < agents->size(); i++) {
            
            // get velocity vector at 'i'
            vec3 v = v_rvo->at(i);
            
            // update the RVO velocity in agent i with v_rvo
            (*agents)[i].setRVO(vec2(v.x, v.y));
        }
    }
}




