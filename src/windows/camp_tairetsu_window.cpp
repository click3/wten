#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;
using namespace boost::assign;

CampTairetsuWindow::CampTairetsuWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::wstring> default_frame_filename) :
	CampBaseWindow(pt, default_frame_filename)
{
}

CampTairetsuWindow::CampTairetsuWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const Graph> default_frame_graph) :
	CampBaseWindow(pt, default_frame_graph)
{
}

CampTairetsuWindow::~CampTairetsuWindow() {
}

boost::optional<boost::shared_ptr<Error> > CampTairetsuWindow::WindowInitialize(void) {
	OPT_ERROR(CampBaseWindow::WindowInitialize());
	if(pt->Size() == 0) {
		OPT_ERROR(SendNextTextWindowEvent(WChar2Ptr(L"PTに所属しているキャラクターが居ません")));
		return boost::none;
	}
	std::vector<boost::shared_ptr<CharData> > char_list = pt->GetCharacters();
	pt->Clear();
	boost::shared_ptr<windows::TairetsuWindow> window(new windows::TairetsuWindow(char_list, true, default_frame_graph));
	OPT_ERROR(window->Move(50, 80));
	OPT_ERROR(window->Resize(540, 260));
	boost::shared_ptr<Event> cancel_event(new events::TairetsuSelectedEvent(char_list));
	window->SetCancelEvent(cancel_event);
	SendNextWindowEvent(window);
	return boost::none;
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type CampTairetsuWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event);
	switch(event->GetEventType()) {
		case EVENT_TYPE_NEXT_STEP: {
			OPT_ERROR(RemoveThisWindow());
			return boost::none;
		}
		case EVENT_TYPE_TAIRETSU_SELECTED: {
			boost::shared_ptr<events::TairetsuSelectedEvent> tairetsu_selected_event = boost::static_pointer_cast<events::TairetsuSelectedEvent>(event);
			BOOST_FOREACH(boost::shared_ptr<CharData> char_data, tairetsu_selected_event->GetCharList()) {
				if(char_data) {
					pt->PushBack(char_data);
				}
			}
			OPT_ERROR(RemoveThisWindow());
			return boost::none;
		}
		case EVENT_TYPE_KEY: {
			return boost::none;
		}
		default:
			break;
	}
	return CampBaseWindow::NotifyEvent(event);
}

} // windows

} // wten
