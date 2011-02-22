#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

UIInputString::UIInputString() {
}

UIInputString::~UIInputString() {
}

boost::optional<boost::shared_ptr<Error> > UIInputString::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIInputString::Draw(unsigned int abs_x, unsigned int abs_y) {
	OPT_STRING_PTR(text, DxLibWrapper::KeyInputString(abs_x, abs_y, 30));
	return boost::none;
}

utility::opt_error<unsigned int>::type UIInputString::CalcWidth() const {
	unsigned int font_width;
	boost::shared_ptr<std::string> str(new std::string("‚ ‚ ‚ ‚ ‚ ‚ ‚ ‚ ‚ ‚ ‚ ‚ ‚ ‚ ‚ "));
	OPT_UINT(font_width, DxLibWrapper::GetFontWidth(str));
	return font_width;
}

utility::opt_error<unsigned int>::type UIInputString::CalcHeight() const {
	unsigned int font_height;
	OPT_UINT(font_height, DxLibWrapper::GetFontHeight());
	return font_height;
}

boost::shared_ptr<std::string> UIInputString::GetText(void) {
	return text;
}

} // uis

} // wten
