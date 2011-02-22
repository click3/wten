#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

namespace {

struct StringToSharedPtr {
	typedef boost::shared_ptr<const std::string> result_type;
	result_type operator ()(const std::string& obj) const {
		return result_type(new std::string(obj));
	}
};

std::vector<boost::shared_ptr<const std::string> > CreateTextList(boost::shared_ptr<const std::string> text) {
	std::vector<std::string> text_list;
	boost::algorithm::split(text_list, *text, boost::is_any_of("\n"));
	std::vector<boost::shared_ptr<const std::string> > result;
	boost::copy(text_list | boost::adaptors::transformed(StringToSharedPtr()), std::back_inserter(result));
	return result;
}

unsigned int CalcTextWidth(boost::shared_ptr<const std::string> text) {
	opt_error<unsigned int>::type width_opt = DxLibWrapper::GetFontWidth(text);
	if(width_opt.which() == 0) {
		boost::get<boost::shared_ptr<Error> >(width_opt)->Abort();
		BOOST_ASSERT(false);
	}
	return boost::get<unsigned int>(width_opt);
}

struct MaxStringWidth {
	bool operator ()(boost::shared_ptr<const std::string> left, boost::shared_ptr<const std::string> right) const {
		return CalcTextWidth(left) < CalcTextWidth(right);
	}
};

struct StringJoin {
	boost::shared_ptr<const std::string> operator ()(boost::shared_ptr<const std::string> left, boost::shared_ptr<const std::string> right) {
		return boost::shared_ptr<const std::string>(new std::string(*left + "\n" + *right));
	}
};

} // anonymous

UIString::UIString(boost::shared_ptr<const std::string> text) :
	UIBase(), text_list(CreateTextList(text))
{
}

UIString::~UIString() {
}

boost::optional<boost::shared_ptr<Error> > UIString::SetText(boost::shared_ptr<const std::string> text) {
	if(!text) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	this->text_list = CreateTextList(text);
	return boost::none;
}

boost::shared_ptr<const std::string> UIString::GetText() const {
	return std::accumulate(text_list.begin(), text_list.end(), boost::shared_ptr<const std::string>(new std::string()), StringJoin());
}

boost::optional<boost::shared_ptr<Error> > UIString::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIString::Draw(unsigned int abs_x, unsigned int abs_y) {
	unsigned int text_width;
	OPT_UINT(text_width, CalcWidth());

	unsigned int text_height;
	OPT_UINT(text_height, CalcHeight());

	unsigned int font_height;
	OPT_UINT(font_height, DxLibWrapper::GetFontHeight());

	const unsigned int draw_x = abs_x + (width - text_width) / 2;
	unsigned int draw_y = abs_y + (height - text_height) / 2;
	BOOST_FOREACH(boost::shared_ptr<const std::string> text, text_list) {
		OPT_ERROR(DxLibWrapper::DrawString(draw_x, draw_y, text, Color(0xFF,0xFF,0xFF)));
		draw_y += font_height;
	}
	return boost::none;
}

opt_error<unsigned int>::type UIString::CalcWidth() const {
	return CalcTextWidth(*std::max_element(text_list.begin(), text_list.end(), MaxStringWidth()));
}

opt_error<unsigned int>::type UIString::CalcHeight() const {
	unsigned int font_height;
	OPT_UINT(font_height, DxLibWrapper::GetFontHeight());
	return font_height * text_list.size();
}

} // uis

} // wten
