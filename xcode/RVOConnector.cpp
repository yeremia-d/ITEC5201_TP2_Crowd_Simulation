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
        
        sim = new RVO::RVOSimulator();
        
        sim->setTimeStep(0.25f);
        sim->setAgentDefaults(15.0f, 10, 10.0f, 5.0f, 2.0f, 2.0f);
        
    }
    
    // Constructor that integrates agent list in system with RVO2 lib system
    RVOConnector::RVOConnector(std::vector<CrowdAgent> * agents) : RVOConnector::RVOConnector() {
        
        this->agents = agents;
        
        for(int i = 0; i < agents->size(); i++) {
            
            CrowdAgent  a       = agents->at(i);            // Gets the agent at i
            vec2        a_pos   = a.getPos();               // Current position of a
            vec2        a_vel   = a.getCurrentVelocity();   // Current Velocity of a
            
            // Adds the agent to the RVO sim
            sim->addAgent(RVO::Vector2(a_pos.x, a_pos.y));
            
            // Updates the radius of the agent
            sim->setAgentRadius(i, a.getRadius());
            
            // Updates the velocity of the agent
            sim->setAgentVelocity(i, RVO::Vector2(a_vel.x, a_vel.y));
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
            
            CrowdAgent a = agents->at(i);           // gets the crowd agent at i
            vec2 vel = a.getCurrentVelocity();      // Gets the current velocity
            vec2 pos = a.getPos();                  // gets the current position
            float r = a.getRadius();                // gets the radius of the agent
            
            sim->setAgentPosition(i, RVO::Vector2(pos.x, pos.y));   // Sets the agent's position
            sim->setAgentVelocity(i, RVO::Vector2(vel.x, vel.y));   // Sets the agent's velocity
            sim->setAgentRadius(i, r);                              // Sets the agent's radius
        }
        
        // Performs a step in the sim with updated/synced values
        sim->doStep();
        
        // Define the vector to return
        std::vector<vec3> RVO_Vel;
        
        // Generate return vector list
        for(int i = 0; i < sim->getNumAgents(); i++) {
            
            RVO::Vector2 v = sim->getAgentVelocity(i);
            
            RVO_Vel.push_back( vec3(v.x(), v.y(), i) );
        }
        
        // Return Vector List
        return RVO_Vel;
    }
    
    // Updates the RVO Velocities
    void RVOConnector::updateRVOVelocities(std::vector<vec3> * v_rvo){
        for(int i = 0; i < agents->size(); i++) {
            vec3 v = v_rvo->at(i);
            // Need to modify a value that has been refernced using a pointer
            (*agents)[i].setRVO(vec2(v.x, v.y));
            
        }
    }
    
    
}
