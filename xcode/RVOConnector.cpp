//
//  RVOConnector.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-17.
//
//

#include "RVOConnector.hpp"
#include "Vector2.h"

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
        }
    }
    
    void RVOConnector::updateRVO() {
        
        // Sync Values in RVO sim
        std::vector<vec3> rvo_base = RVOCalc(5.0f);
        
        // For each level of i lookahead steps, increase radius by n
        
        //compute RVO's with increased radii
        
        // Sum RVO's based on the level of i
        
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
            
            // Sets the agent's velocity
            sim->setAgentVelocity(i, RVO::Vector2(vel.x, vel.y));
            
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
    
    void RVOConnector::solveCollisions() {
        
    }
}


