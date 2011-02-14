#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

UIStringBox::UIStringBox(const std::string& filename, const std::string& text) :
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

boost::optional<boost::shared_ptr<Error> > UIStringBox::SetText(const std::string& text) {
	boost::shared_ptr<UIString> str = boost::static_pointer_cast<UIString>(inner_ui);
	return str->SetText(text);
}


} // uis

} // wten
