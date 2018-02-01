#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "bluecadet/views/BaseView.h"
#include "bluecadet/views/TextView.h"
#include "bluecadet/views/EllipseView.h"
namespace nps {
	typedef std::shared_ptr<class CurvedTextView> CurvedTextViewRef;

		class CurvedTextView : public bluecadet::views::BaseView {

		public:
			CurvedTextView();
			~CurvedTextView();

			void setup(const std::wstring& text = L"", const std::string& styleKey = "", const float radius = 160, const bool parseText = true);
			void setup(const std::string& text = "", const std::string& styleKey = "", const float radius = 160, const bool parseText = true);
	
			// Setters
			void setText(std::wstring text, std::string string);
			void setText(std::string text, std::string string) { setText(bluecadet::text::wideString(text), string); }
			void setRadius(float radius);
			void setStyle(std::string string);
			void setParseValue(const bool parseText);
			void clearText();
			//Getters

		protected:

			void generateLayout();
			void generateLetters();
			//views
			bluecadet::views::BaseViewRef	mTextContainer;
	

			//properties
			int											mTotalWidth = 0;
			std::vector<bluecadet::views::TextViewRef>	mLettersArray;
			std::wstring								mText;
			int											mRadius = 0;
			float										mHeightOfView = 0;
			std::string									mStyle;
			bool										mParseValue = true;
	
			//constants
		};

}
