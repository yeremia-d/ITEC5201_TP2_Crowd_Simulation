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
        sim->setAgentDefaults(200.0f, 10, 10.0f, 5.0f, 2.0f, 2.0f);
        
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
        
        // Get state of system (extrapolated positions of all agents) from t_0 to t_maxIterations
        for(int i = 0; i < AgentConst::MAX_LOOK_AHEAD_STEPS; i++) {
            
            // Declare row that will hold positions of agents at time t_i
            std::vector<vec3> row;
            
            // Compute new positions for all agents (iterate through agents
            for(int agent_id = 0; agent_id < agents->size(); agent_id++) {
                
                // Compute new position
                vec2 newPosition = (*agents)[agent_id].getPos() + ((float)i * (*agents)[agent_id].getCurrentVelocity() / ci::app::getFrameRate() );
                
                // push new position to row
                row.push_back(vec3(newPosition.x, newPosition.y, agent_id));
            }
            
            // Add row to list of positions from t_0 to t_maxIterations
            LR_pos.push_back(row);
        }
        
        // Compute RVO for all (due to the way the library works)
        for(int i = 0; i < LR_pos.size(); i++) {
            
            // Solve RVO velocities based on t_i parameters (positions and radii)
            std::vector<vec3> LR_rvoList_i = RVOCalc((1/((float)i + 1)) * AgentConst::AGENT_RADIUS, &LR_pos[i]);
            
            // Add the computed RVO velocities to LR_vel list
            LR_vel.push_back(LR_rvoList_i);
        }
        
        // Update curtailing factor on all agents based on velocity
            // update curtailing fn that updates max num of iterations based on current vel of agent
        
        // iterate through each time step,
            // on each iteration, iterate through agents. if i <= iMax for specific agents, then apply RVO with agent radius adjusted for the timestep, if not, continue
        
        // Declare RVO velocities with Look Ahead
        std::vector<vec3> RVO_LR;
        
        // Default, use all
        for(int i = 0; i < agents->size(); i++) {
            
            vec3 v = vec3();
            
            for(int j = 0; j < AgentConst::MAX_LOOK_AHEAD_STEPS; j++) {
                v.x += (1/(j+1))*LR_vel[j][i].x;
                v.y += (1/(j+1))*LR_vel[j][i].y;
                v.z  = LR_vel[j][i].z;
            }
            RVO_LR.push_back(v);
        }
        
        return RVO_LR;
        
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




