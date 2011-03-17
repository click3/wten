#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

UIInputDlg::UIInputDlg(boost::shared_ptr<const std::wstring> message, boost::shared_ptr<const std::wstring> frame_filename) :
	UIBox(frame_filename), ui_input_string(new UIInputString())
{
	boost::optional<boost::shared_ptr<Error> > error;
	BOOST_ASSERT(ui_input_string);
	boost::shared_ptr<UIBox> ui_box(new UIBox(frame_filename));
	if(error = ui_box->SetInnerUI(ui_input_string)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	boost::shared_ptr<UIString> ui_message(new UIString(message));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > ui_list;
	ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, ui_message);
	ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, ui_box);
	boost::shared_ptr<UIQueue> ui_queue(new UIQueue(ui_list, UIQueue::INNER_POSITION_CENTER));

	if(error = SetInnerUI(ui_queue)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

UIInputDlg::~UIInputDlg() {
}

boost::shared_ptr<std::wstring> UIInputDlg::GetText(void) const {
	return ui_input_string->GetText();
}

} // uis

} // wten
