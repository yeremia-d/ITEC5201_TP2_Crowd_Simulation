#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

// TEST

#include "CrowdAgent.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HLRCA_CrowdSimApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    
    CrowdAgent a;
    
};

void HLRCA_CrowdSimApp::setup()
{
    a = CrowdAgent();
}

void HLRCA_CrowdSimApp::mouseDown( MouseEvent event )
{
}

void HLRCA_CrowdSimApp::update()
{
}

void HLRCA_CrowdSimApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    a.draw();
}

CINDER_APP( HLRCA_CrowdSimApp, RendererGl, [&]( App::Settings *settings ) {
    settings->setWindowSize( 1280, 720 );
})
