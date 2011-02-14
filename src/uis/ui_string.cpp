#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

UIString::UIString(const std::string& text) :
	UIBase(), text(text)
{
}

UIString::~UIString() {
}

boost::optional<boost::shared_ptr<Error> > UIString::SetText(const std::string& text) {
	this->text = text;
	return boost::none;
}

opt_error<std::string>::type UIString::GetText() {
	return text;
}

boost::optional<boost::shared_ptr<Error> > UIString::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIString::Draw(unsigned int abs_x, unsigned int abs_y) {
	boost::optional<boost::shared_ptr<Error> > error;
	unsigned int font_width;
	{
		opt_error<unsigned int>::type width_opt = DxLibWrapper::GetFontWidth(text);
		if(width_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(width_opt);
		}
		font_width = boost::get<unsigned int>(width_opt);
	}

	unsigned int font_height;
	{
		opt_error<unsigned int>::type height_opt = DxLibWrapper::GetFontHeight();
		if(height_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(height_opt);
		}
		font_height = boost::get<unsigned int>(height_opt);
	}

	const unsigned int draw_x = abs_x + (width - font_width) / 2;
	const unsigned int draw_y = abs_y + (height - font_height) / 2;

	error = DxLibWrapper::DrawString(draw_x, draw_y, text, Color(0xFF,0xFF,0xFF));
	if(error) {
		return error.get();
	}
	return boost::none;
}

opt_error<unsigned int>::type UIString::CalcWidth() {
	unsigned int font_width;
	{
		opt_error<unsigned int>::type width_opt = DxLibWrapper::GetFontWidth(text);
		if(width_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(width_opt);
		}
		font_width = boost::get<unsigned int>(width_opt);
	}
	return font_width;
}

opt_error<unsigned int>::type UIString::CalcHeight() {
	unsigned int font_height;
	{
		opt_error<unsigned int>::type height_opt = DxLibWrapper::GetFontHeight();
		if(height_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(height_opt);
		}
		font_height = boost::get<unsigned int>(height_opt);
	}
	return font_height;
}

} // uis

} // wten
