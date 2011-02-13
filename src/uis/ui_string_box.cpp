#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

UIStringBox::UIStringBox(const std::string& filename, const std::string& text) :
	UIBox(filename), text(text)
{
}

UIStringBox::~UIStringBox() {
}

boost::optional<boost::shared_ptr<Error> > UIStringBox::SetText(const std::string& text) {
	std::string temp_text = this->text;
	this->text = text;
	boost::optional<boost::shared_ptr<Error> > error = PointAndSizeIsValid();
	if(error) {
		opt_error<unsigned int>::type width = CalcWidth();
		if(width.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(width);
		}
		opt_error<unsigned int>::type height = CalcHeight();
		if(height.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(height);
		}
		error = Resize(boost::get<unsigned int>(width), boost::get<unsigned int>(height));
		if(error) {
			this->text = temp_text;
			return error.get();
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIStringBox::PointAndSizeIsValid(void) {
	opt_error<unsigned int>::type width = CalcWidth();
	if(width.which() == 0) {
		return boost::get<boost::shared_ptr<Error> >(width);
	}
	opt_error<unsigned int>::type height = CalcHeight();
	if(height.which() == 0) {
		return boost::get<boost::shared_ptr<Error> >(height);
	}
	if(this->width < boost::get<unsigned int>(width) || this->height < boost::get<unsigned int>(height)) {
		return CreateError(ERROR_CODE_OUTSIDE_RANGE);
	}
	return UIBox::PointAndSizeIsValid();
}

boost::optional<boost::shared_ptr<Error> > UIStringBox::Draw(void) {
	boost::optional<boost::shared_ptr<Error> > error = UIBox::Draw();
	if(error) {
		return error.get();
	}

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

	unsigned int x;
	unsigned int y;
	{
		opt_error<boost::tuple<unsigned int, unsigned int> >::type pos_opt = GetAbsolutePoint();
		if(pos_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(pos_opt);
		}
		boost::tie(x, y) = boost::get<boost::tuple<unsigned int, unsigned int> >(pos_opt);
	}

	const unsigned int draw_x = x + (width - font_width) / 2;
	const unsigned int draw_y = y + (height - font_height) / 2;

	error = DxLibWrapper::DrawString(draw_x, draw_y, text, Color(0xFF,0xFF,0xFF));
	if(error) {
		return error.get();
	}
	return boost::none;
}

opt_error<unsigned int>::type UIStringBox::CalcWidth() {
	unsigned int font_width;
	{
		opt_error<unsigned int>::type width_opt = DxLibWrapper::GetFontWidth(text);
		if(width_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(width_opt);
		}
		font_width = boost::get<unsigned int>(width_opt);
	}
	return left_up->GetWidth() + right_up->GetWidth() + font_width;
}

opt_error<unsigned int>::type UIStringBox::CalcHeight() {
	unsigned int font_height;
	{
		opt_error<unsigned int>::type height_opt = DxLibWrapper::GetFontHeight();
		if(height_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(height_opt);
		}
		font_height = boost::get<unsigned int>(height_opt);
	}
	return left_up->GetHeight() + left_down->GetHeight() + font_height;
}

} // uis

} // wten
