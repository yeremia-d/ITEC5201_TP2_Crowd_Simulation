#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

// TEST

#include "CrowdSim.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HLRCA_CrowdSimApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    CrowdSim* sim = new CrowdSim();
    
    // appState = 0 -> calculating
    // appState = 1 -> show sim
    int appState = 0;
    int simTime = 5 * 30;
    int currentFrame = 0;
    
    std::vector<std::vector<vec2>> positions;
    
};

// Initialize Simulation
void HLRCA_CrowdSimApp::setup() {
    sim->initBidirectionalSim();
}

// Handle Mousedown event
void HLRCA_CrowdSimApp::mouseDown( MouseEvent event ) {}

// Update function during execution loop
void HLRCA_CrowdSimApp::update() {
    if(appState == 0) {
    // Update Simulation
        if(currentFrame < simTime) {
            sim->update();
                
            std::vector<vec2> pos = sim->getAgentPositions();
            positions.push_back(pos);
            currentFrame++;
        } else {
            appState = 1;
            
           
        }
    }
}

// Draw action during execution loop
void HLRCA_CrowdSimApp::draw() {
    
    // Clear the screen
    gl::clear( Color( 0, 0, 0 ) );
    
    if(appState == 0) {
        string message = "Computing Simulation - Frame " +  std::to_string(currentFrame) + " of " + std::to_string(simTime);
        
        gl::drawString(message, vec2(10.0f,10.0f));
    }
    
    else {
        
        if(currentFrame >= simTime) {
            currentFrame = 0;
        }
        
        for(int i = 0; i < positions[currentFrame].size(); i++) {
            vec2 agent_position = positions[currentFrame].at(i);
            gl::drawSolidCircle(agent_position, 10.0f);
        }
        
        currentFrame++;
        
        // Draw the simulation
        //sim->draw();
    }
   
    
    
}

// App parameters and settings
CINDER_APP( HLRCA_CrowdSimApp, RendererGl, [&]( App::Settings *settings ) { settings->setWindowSize( 1280, 720 );})
