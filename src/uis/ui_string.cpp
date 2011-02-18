#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

UIString::UIString(boost::shared_ptr<const std::string> text) :
	UIBase(), text(text)
{
}

UIString::~UIString() {
}

boost::optional<boost::shared_ptr<Error> > UIString::SetText(boost::shared_ptr<const std::string> text) {
	if(!text) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	this->text = text;
	return boost::none;
}

boost::shared_ptr<const std::string> UIString::GetText() const {
	return text;
}

boost::optional<boost::shared_ptr<Error> > UIString::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIString::Draw(unsigned int abs_x, unsigned int abs_y) {
	unsigned int font_width;
	OPT_UINT(font_width, DxLibWrapper::GetFontWidth(text));

	unsigned int font_height;
	OPT_UINT(font_height, DxLibWrapper::GetFontHeight());

	const unsigned int draw_x = abs_x + (width - font_width) / 2;
	const unsigned int draw_y = abs_y + (height - font_height) / 2;

	OPT_ERROR(DxLibWrapper::DrawString(draw_x, draw_y, text, Color(0xFF,0xFF,0xFF)));
	return boost::none;
}

opt_error<unsigned int>::type UIString::CalcWidth() const {
	unsigned int font_width;
	OPT_UINT(font_width, DxLibWrapper::GetFontWidth(text));
	return font_width;
}

opt_error<unsigned int>::type UIString::CalcHeight() const {
	unsigned int font_height;
	OPT_UINT(font_height, DxLibWrapper::GetFontHeight());
	return font_height;
}

} // uis

} // wten
