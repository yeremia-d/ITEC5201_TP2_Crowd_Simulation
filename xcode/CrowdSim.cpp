//
//  CrowdSim.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdSim.h"

CrowdSim::CrowdSim() {
}

void CrowdSim::initBidirectionalSim() {
    
    for(int i = 50; i < 300; i +=25)
        for(int j = 100; j < 600; j +=25) {
            // Create New CrowdAgent
            CrowdAgent a = CrowdAgent(vec2(i,j), vec2(i+(rand() % 500 + 300), j));
            
            // Sets UID for crowd Agent
            a.setId(agents.size());
            
            // Initialize Forces
            a.update();
            
            // Adds new Crowd Agent to agents list
            agents.push_back(a);
        }
    
    // Initialize RVO Adaptor
    RVO2Adaptor = RVOConn::RVOConnector(&agents);
    
}

// Update Agents positions
void CrowdSim::update() {
    
    //Solve for Collisions
    RVO2Adaptor.solveCollisions();
    
    // Update RVO Velocities of the Agents
    RVO2Adaptor.updateRVO();
    
    // Update Agents
    for(int i = 0; i < agents.size(); i++) agents[i].update();
    
}

// Draws the agents in the groups
void CrowdSim::draw() {
    
    // Clears Canvas
    gl::clear();
    
    // Draws Agents
    for(int i = 0; i < agents.size(); i++) {
        gl::color(agents[i].getColor());
        gl::drawSolidCircle(agents[i].getPos(), agents[i].getRadius());
    }
}




