#include "cinder/Log.h"
#include <string>

#include "CurvedTextView.h"
#include "bluecadet/core/SettingsManager.h"
#include "bluecadet/core/ScreenLayout.h"
#include "bluecadet/utils/ImageManager.h"
#include "bluecadet/views/TextView.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace bluecadet;
using namespace bluecadet::core;
using namespace bluecadet::views;
using namespace bluecadet::utils;

namespace nps {
	CurvedTextView::CurvedTextView() : BaseView() {
	}

	CurvedTextView::~CurvedTextView() {
	}


	void CurvedTextView::setup(const std::wstring& text, const std::string& styleKey, const float radius, const bool parseText) {
		setParseValue(parseText);
		setText(text, styleKey);
		setRadius(radius);
	}
	void CurvedTextView::setup(const std::string& text, const std::string& styleKey, const float radius, const bool parseText) {
		setup(text::wideString(text), styleKey, radius, parseText);
	}
	void CurvedTextView::setParseValue(const bool parseText) {
		mParseValue = parseText;
	}

	void CurvedTextView::setText(std::wstring text, std::string string)
	{
		mText = text;
		setStyle(string);
		generateLetters();
		generateLayout();
	}

	void CurvedTextView::setRadius(float radius)
	{
		mRadius = radius;
		generateLetters();
		generateLayout();
	}

	void CurvedTextView::setStyle(std::string string)
	{
		mStyle = string;
	}

	void CurvedTextView::generateLayout()
	{

		//float midPointCoordinates;
		float offset = 0;
		float midPointOfString = (mTotalWidth) / 2;
		float bufferedRadius = mRadius + mHeightOfView;

		for (auto letter : mLettersArray) {
			//get next degree for letter or space based off of the offset distance away from the midpoint
			float rel = (offset - midPointOfString);

			//convert degrees to radians
			//Angle in radians is the arclength divided by the radius
			//Starting on the top side of the circle by adding -M_PI/2
			float angle = -M_PI / 2 + rel / bufferedRadius;

			//calc x and y coordinates based off of the angle
			float x = bufferedRadius * (cos(angle));
			float y = bufferedRadius * (sin(angle));

			//set position 
			letter->setPosition(vec2(x, y));

			//set offset for next letter by adding the letter width
			offset = offset + letter->getTextWidth();
			letter->setTransformOrigin(vec2(letter->getWidth() / 2, letter->getHeight() / 2));

			//calc rotation, at -90 because we rotated the circle to place the text at the top
			float rotation = atan2(0, -90) - atan2(x, y);
			letter->setRotation(rotation);

			//reset transformOrigin
			letter->setTransformOrigin(vec2(0));

		}

	}

	void CurvedTextView::generateLetters()
	{
		clearText();
		int count = 0;
		const int stringLength = mText.length();
		mTotalWidth = 0;

		for (int i = 0; i < stringLength; ++i) {
			//make text view and add properties
			TextViewRef letter = make_shared<TextView>();

			letter->setup(mText.substr(i, 1), mStyle, mParseValue);

			//set parseText to false for spaces or they will be removed
			if (letter->getWidth() == 0) {
				letter->setup(mText.substr(i, 1), mStyle, false);
			}
			//calculate the height of the view so you can place the text on the curve
			if (count == 0) {
				mHeightOfView = abs(letter->getHeight());
			}

			//add text to container so we can position the letters as a whole within the view
			addChild(letter);

			//calculate total width of the string
			mTotalWidth = mTotalWidth + letter->getTextWidth();

			//add to array
			mLettersArray.push_back(letter);
			count++;
		}
	}

	void CurvedTextView::clearText()
	{
		//loop through and set each to a nullptr 
		for (auto letter : mLettersArray) {
			letter = nullptr;
		}
		mLettersArray.clear();
		removeAllChildren();
	}
}
