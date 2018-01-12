#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "bluecadet/text/Text.h"
#include "bluecadet/text/StyledTextLayout.h"
#include "bluecadet/text/StyleManager.h"

#include "BaseView.h"
#include "TextView.h"

//TextView extended class to hold positions of where
//the text displays, where it comes from and where it goes
typedef std::shared_ptr<class TextViewExt> TextViewExtRef;
	
class TextViewExt : public bluecadet::views::TextView {

public:

	ci::vec2	displayPos;
	ci::vec2	enterFromPos;
	ci::vec2	leaveToPos;

	void show(float duration = 0.0f, cinder::EaseFn easeFunction = cinder::EaseNone(), float delay = 0.0f) {
		getTimeline()->apply(&getPosition(), displayPos, duration, easeFunction).delay(delay);
		getTimeline()->apply(&getAlpha(), 1.0f, duration, easeFunction).delay(delay);
	}

	void hide(float duration = 0.0f, cinder::EaseFn easeFunction = cinder::EaseNone(), float delay = 0.0f ) {
		getTimeline()->apply(&getPosition(), leaveToPos, duration, easeFunction).delay(delay);
		getTimeline()->apply(&getAlpha(), 0.0f, duration, easeFunction).delay(delay);
	}

};
