#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

UIStringBox::UIStringBox(boost::shared_ptr<const std::wstring> filename, boost::shared_ptr<const std::wstring> text) :
	UIBox(filename)
{
	boost::shared_ptr<UIString> str(new UIString(text));
	BOOST_ASSERT(str);
	boost::optional<boost::shared_ptr<Error> > error = SetInnerUI(str);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

UIStringBox::~UIStringBox() {
}


boost::shared_ptr<const std::wstring> UIStringBox::GetText() const {
	boost::shared_ptr<UIString> str = boost::static_pointer_cast<UIString>(inner_ui);
	BOOST_ASSERT(str);
	return str->GetText();
}

boost::optional<boost::shared_ptr<Error> > UIStringBox::SetText(boost::shared_ptr<const std::wstring> text) {
	boost::shared_ptr<UIString> str = boost::static_pointer_cast<UIString>(inner_ui);
	return str->SetText(text);
}


} // uis

} // wten
