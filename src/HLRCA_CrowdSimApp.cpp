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

void HLRCA_CrowdSimApp::setup()                         { sim->initBidirectionalSim(); }                // Initialize Simulation
void HLRCA_CrowdSimApp::mouseDown( MouseEvent event )   {}
void HLRCA_CrowdSimApp::update()                        { sim->update(); }                              // Update Simulation
void HLRCA_CrowdSimApp::draw()                          { gl::clear( Color( 0, 0, 0 ) ); sim->draw(); } // Draw Agents

CINDER_APP( HLRCA_CrowdSimApp, RendererGl, [&]( App::Settings *settings ) { settings->setWindowSize( 1280, 720 );})
