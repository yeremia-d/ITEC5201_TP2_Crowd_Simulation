//
//  CrowdSim.cpp
//  HLRCA_CrowdSim
//
//  Created by Yeremia on 2017-04-06.
//
//

#include "CrowdSim.h"

void CrowdSim::initBidirectionalSim() {
    
    // Create Larger Crowd going left to right
    for(int i = 50; i < 300; i +=25)
        for(int j = 100; j < 600; j +=25) {
            // Create New CrowdAgent
            CrowdAgent a = CrowdAgent(vec2(i,j), vec2(app::getWindowSize().x, j));
            
            // Sets UID for crowd Agent
            a.setId(agents.size());
            
            // Sets Color of agent
            a.setColor(Color(1,0,0));
            
            // Initialize Forces
            a.update();
            
            // Adds new Crowd Agent to agents list
            agents.push_back(a);
        }
    
    // Create Smaller Crowd going left to right
    for(int i = 350; i < 600; i +=25)
        for(int j = 200; j < 300; j +=25) {
            // Create New CrowdAgent
            CrowdAgent a = CrowdAgent(vec2(i,j), vec2(0, j));
            
            // Sets UID for crowd Agent
            a.setId(agents.size());
            
            // Sets Color of agent
            a.setColor(Color(0,0,1));
            
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




