#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define SCENE_SIZE 800
#define BLUR_SIZE 200

struct Box {
	vec2 pos, vel;
	ColorA col;
	float width;
	Rectf rect;
};

class SimpleBlurApp : public App {
  public:

	static void prepare(Settings *settings);

	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	void drawBoxes();

	gl::FboRef mFboScene;
	gl::FboRef mFboBlur1;
	gl::FboRef mFboBlur2;

	gl::GlslProgRef mBlurShader;

	vector<Box>	mBoxes;

};

void SimpleBlurApp::prepare(Settings *settings)
{
	settings->setResizable(false);
	settings->setWindowSize(800, 800);
	settings->setTitle("Simple Blur Test");
}


void SimpleBlurApp::setup()
{
	//setup the scene:
	//Draw a bunch of boxes in different colors at random positions
	for (int i = 0; i < 10; i++) {
		Box b;
		b.pos = vec2(Rand::randInt(getWindowWidth()), Rand::randInt(getWindowHeight()));
		b.vel = vec2(Rand::randFloat(-3.0f, 3.0f), Rand::randFloat(-3.0f, 3.0f));
		b.col = ColorA( hsvToRgb( vec3(Rand::randFloat(1.0f), 0.75f, 1.0f)), 1.0f);
		b.width = Rand::randFloat(10.0f, 100.0f);
		b.rect = Rectf( b.pos.x, b.pos.y, b.pos.x + b.width, b.pos.y + b.width );
		mBoxes.push_back(b);
	}

	//setup the fbos and shaders
	mFboScene = gl::Fbo::create(SCENE_SIZE, SCENE_SIZE);

	// setup our blur Fbo's, smaller ones will generate a bigger blur
	mFboBlur1 = gl::Fbo::create(BLUR_SIZE, BLUR_SIZE);
	mFboBlur2 = gl::Fbo::create(BLUR_SIZE, BLUR_SIZE);

	// load and compile the shaders
	try {
		mBlurShader = gl::GlslProg::create(loadAsset("blur.vert"), loadAsset("blur.frag"));	
	}
	catch (const std::exception &e) {
		console() << e.what() << endl;
		quit();
	}



}

void SimpleBlurApp::mouseDown( MouseEvent event )
{
}

void SimpleBlurApp::update()
{
	//move the boxes around
	for (int i = 0; i < mBoxes.size(); i++ ) {

		mBoxes[i].pos += mBoxes[i].vel;

		//wrap
		if (mBoxes[i].pos.x < 0) {
			mBoxes[i].pos.x = getWindowWidth();
		}
		if (mBoxes[i].pos.x > getWindowWidth()) {
			mBoxes[i].pos.x = 0;
		}
		if (mBoxes[i].pos.y < 0) {
			mBoxes[i].pos.y = getWindowHeight();
		}
		if (mBoxes[i].pos.y > getWindowHeight()) {
			mBoxes[i].pos.y = 0;
		}

		mBoxes[i].rect = Rectf(mBoxes[i].pos.x, mBoxes[i].pos.y, mBoxes[i].pos.x + mBoxes[i].width, mBoxes[i].pos.y + mBoxes[i].width);
	}



	gl::pushMatrices();

	// draw boxes into fbo
	{
		gl::ScopedFramebuffer fbo(mFboScene);
		gl::ScopedViewport    viewport(0, 0, mFboScene->getWidth(), mFboScene->getHeight());

		gl::setMatricesWindow(SCENE_SIZE, SCENE_SIZE);
		gl::clear(ColorA::gray(0.0f, 0.0f));
		drawBoxes();
	}


	//set the amount of blurring based on mouse X position
	vec2 n = vec2(getMousePos().x / (float)getWindowWidth(), getMousePos().y / (float)getWindowHeight());

	//bind the blur shader
	{
		gl::ScopedGlslProg shader(mBlurShader);
		mBlurShader->uniform("tex0", 0); // use texture unit 0

		// tell the shader to blur horizontally and the size of 1 pixel
		mBlurShader->uniform("sample_offset", vec2(1.0f / mFboBlur1->getWidth(), 0.0f));
		mBlurShader->uniform("attenuation", n.x);

		//do horizontal blurring first
		{
			gl::ScopedFramebuffer fbo(mFboBlur1);
			gl::ScopedViewport    viewport(0, 0, mFboBlur1->getWidth(), mFboBlur1->getHeight());
			gl::ScopedTextureBind tex0(mFboScene->getColorTexture(), (uint8_t)0);

			gl::setMatricesWindow(BLUR_SIZE, BLUR_SIZE);
			gl::clear(ColorA::gray(0.0f, 0.0f));
			gl::drawSolidRect(mFboBlur1->getBounds());
		}

		// tell the shader to blur vertically and the size of 1 pixel
		mBlurShader->uniform("sample_offset", vec2(0.0f, 1.0f / mFboBlur2->getHeight()));
		mBlurShader->uniform("attenuation", n.x);

		{
			gl::ScopedFramebuffer fbo(mFboBlur2);
			gl::ScopedViewport    viewport(0, 0, mFboBlur2->getWidth(), mFboBlur2->getHeight());
			gl::ScopedTextureBind tex0(mFboBlur1->getColorTexture(), (uint8_t)0);

			gl::setMatricesWindow(BLUR_SIZE, BLUR_SIZE);
			gl::clear(ColorA::gray(0.0f, 0.0f));
			gl::drawSolidRect(mFboBlur2->getBounds());
		}

	}

	gl::popMatrices();


}

void SimpleBlurApp::drawBoxes(){
	for (int i = 0; i < mBoxes.size(); i++) {
		gl::color(mBoxes[i].col);
		gl::drawSolidRect(mBoxes[i].rect);
	}
}

void SimpleBlurApp::draw()
{
	//gl::clear( Color( 0, 0, 0 ) ); 

	//draw stripes behind outside of blur effect
	int numStripes = 20;
	for (int i = 0; i < 20; i++) {

		if (i % 2 == 0) {
			gl::color(ColorA::gray(1.0f, 1.0f));
		} else {
			gl::color(ColorA::gray(0.0f, 1.0f));
		}
		float width = getWindowWidth()/ numStripes;

		gl::drawSolidRect(Rectf( i * width, 0.0f, (i+1) * width, getWindowHeight()  ));

	}


	// draw the actual Fbos
	gl::ScopedBlendPremult scpBlend;
	gl::color(Color::white());
	gl::draw(mFboScene->getColorTexture(), Rectf(0, 0, getWindowWidth(), getWindowHeight()));

	//draw the blurred fbo on top
	gl::draw(mFboBlur2->getColorTexture(), Rectf( 0, 0, getWindowWidth(), getWindowHeight()) );

}

CINDER_APP( SimpleBlurApp, RendererGl(RendererGl::Options().msaa(16)), &SimpleBlurApp::prepare)
