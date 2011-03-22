#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

namespace {

struct StringToSharedPtr {
	typedef boost::shared_ptr<const std::wstring> result_type;
	result_type operator ()(const std::wstring& obj) const {
		return result_type(new std::wstring(obj));
	}
};

std::vector<boost::shared_ptr<const std::wstring> > CreateTextList(const wchar_t *text) {
	BOOST_ASSERT(text != NULL);
	std::vector<std::wstring> text_list;
	boost::algorithm::split(text_list, text, boost::is_any_of(L"\n"));
	std::vector<boost::shared_ptr<const std::wstring> > result;
	boost::copy(text_list | boost::adaptors::transformed(StringToSharedPtr()), std::back_inserter(result));
	return result;
}
std::vector<boost::shared_ptr<const std::wstring> > CreateTextList(const char *text) {
	BOOST_ASSERT(text != NULL);
	if(*text == '\0') {
		return CreateTextList(L"");
	}
	std::vector<wchar_t> buffer;
	boost::optional<boost::shared_ptr<Error> > error = UTF8ToWChar(text, &buffer);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	return CreateTextList(&buffer.front());
}
std::vector<boost::shared_ptr<const std::wstring> > CreateTextList(boost::shared_ptr<const std::string> text) {
	return CreateTextList(text->c_str());
}
std::vector<boost::shared_ptr<const std::wstring> > CreateTextList(boost::shared_ptr<const std::wstring> text) {
	return CreateTextList(text->c_str());
}
std::vector<boost::shared_ptr<const std::wstring> > CreateTextList(const std::string &text) {
	return CreateTextList(text.c_str());
}
std::vector<boost::shared_ptr<const std::wstring> > CreateTextList(const std::wstring &text) {
	return CreateTextList(text.c_str());
}


unsigned int CalcTextWidth(boost::shared_ptr<const std::wstring> text) {
	opt_error<unsigned int>::type width_opt = DxLibWrapper::GetFontWidth(text);
	if(width_opt.which() == 0) {
		boost::get<boost::shared_ptr<Error> >(width_opt)->Abort();
		BOOST_ASSERT(false);
	}
	return boost::get<unsigned int>(width_opt);
}

struct MaxStringWidth {
	bool operator ()(boost::shared_ptr<const std::wstring> left, boost::shared_ptr<const std::wstring> right) const {
		return CalcTextWidth(left) < CalcTextWidth(right);
	}
};

struct StringJoin {
	boost::shared_ptr<const std::wstring> operator ()(boost::shared_ptr<const std::wstring> left, boost::shared_ptr<const std::wstring> right) {
		return boost::shared_ptr<const std::wstring>(new std::wstring(*left + L"\n" + *right));
	}
};

} // anonymous

UIString::UIString(boost::shared_ptr<const std::string> text) : text_list(CreateTextList(text)) { }
UIString::UIString(boost::shared_ptr<const std::wstring> text) : text_list(CreateTextList(text)) { }
UIString::UIString(const std::string &text) : text_list(CreateTextList(text)) { }
UIString::UIString(const std::wstring &text) : text_list(CreateTextList(text)) { }
UIString::UIString(const char *text) : text_list(CreateTextList(text)) { }
UIString::UIString(const wchar_t *text) : text_list(CreateTextList(text)) { }

UIString::~UIString() {
}

boost::optional<boost::shared_ptr<Error> > UIString::SetText(boost::shared_ptr<const std::string> text) {
	if(!text) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	this->text_list = CreateTextList(text);
	return boost::none;
}
boost::optional<boost::shared_ptr<Error> > UIString::SetText(boost::shared_ptr<const std::wstring> text) {
	if(!text) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	this->text_list = CreateTextList(text);
	return boost::none;
}
boost::optional<boost::shared_ptr<Error> > UIString::SetText(const std::string &text) {
	this->text_list = CreateTextList(text);
	return boost::none;
}
boost::optional<boost::shared_ptr<Error> > UIString::SetText(const std::wstring &text) {
	this->text_list = CreateTextList(text);
	return boost::none;
}
boost::optional<boost::shared_ptr<Error> > UIString::SetText(const char *text) {
	this->text_list = CreateTextList(text);
	return boost::none;
}
boost::optional<boost::shared_ptr<Error> > UIString::SetText(const wchar_t *text) {
	this->text_list = CreateTextList(text);
	return boost::none;
}

boost::shared_ptr<const std::wstring> UIString::GetText() const {
	return std::accumulate(text_list.begin(), text_list.end(), boost::shared_ptr<const std::wstring>(new std::wstring()), StringJoin());
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
	BOOST_FOREACH(boost::shared_ptr<const std::wstring> text, text_list) {
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
