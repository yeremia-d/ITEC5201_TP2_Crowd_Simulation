#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HLRCA_CrowdSimApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void HLRCA_CrowdSimApp::setup()
{
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
}

CINDER_APP( HLRCA_CrowdSimApp, RendererGl )
