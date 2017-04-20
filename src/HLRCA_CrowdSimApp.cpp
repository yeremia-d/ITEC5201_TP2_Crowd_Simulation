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
    
};

// Initialize Simulation
void HLRCA_CrowdSimApp::setup() {
    sim->initBidirectionalSim();
}

// Handle Mousedown event
void HLRCA_CrowdSimApp::mouseDown( MouseEvent event ) {}

// Update function during execution loop
void HLRCA_CrowdSimApp::update() {
    
    // Update Simulation
    sim->update();
}

// Draw action during execution loop
void HLRCA_CrowdSimApp::draw() {
    
    // Clear the screen
    gl::clear( Color( 0, 0, 0 ) );
    
    // Draw the simulation
    sim->draw();
}

// App parameters and settings
CINDER_APP( HLRCA_CrowdSimApp, RendererGl, [&]( App::Settings *settings ) { settings->setWindowSize( 1280, 720 );})
