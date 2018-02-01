# CurvedTextView

This class came in handy in a project that required text on a curve. By default, the text will be positioned on top of the curve. 


## Use Case:

//In header

```C++

#include "bluecadet/views/CurvedTextView.h"

CurvedTextViewRef mCurvedText;

```

//In CPP

```C++

	//setup/initialize object by passing the text, styles, radius, and parse boolean value to the setup function
	mCurvedText = make_shared<CurvedTextView>();
	mCurvedText->setup("text", "[style]", 200, true);
	addChild(mCurvedText);

```