# TextViewExtended

This class came in handy in a project that required lots of text elements to animate on and off in similar ways. This version will fade text in and tween it from a different position on "show()" and tween it to different position and fade it out on "hide()".

Declare 3 positions (home, where it's coming from and where it goes to) then call show and hide to bring them in and out respectively. Just place the header file in the same location as the TextView class inside Bluecadet's views block. 


## Use Case:

//In header

```C++

#include "bluecadet/views/TextViewExt.h"

TextViewExtRef mText;

```

//In CPP

```C++

	//setup/initialize object
	mText = make_shared<TextViewExt>();
	mText->setup("Texty Text");
	mText->setTextColor(ColorA::gray(1.0f));
	mText->setAlpha(0.0f);

	//declare the three position
	mText->displayPos		= vec2(100, 100);
	mText->enterFromPos		= mTitle->displayPos + vec2( 200, 0);
	mText->leaveToPos		= mTitle->displayPos + vec2(-200, 0);
	mText->setPosition(mTitle->enterFromPos);
	addChild(mTitle);


	//to show/hide instantly with no tween:
	mText->show();
	mText->hide();


	//can also feed in parameters
	float duration = 1.0f;
	float delay = 0.5f;
	mText->show( duration, EaseInOutQuad(), delay);

```