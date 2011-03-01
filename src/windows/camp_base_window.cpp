#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;
using namespace boost::assign;

CampBaseWindow::CampBaseWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::string> default_frame_filename) :
	WindowBase(default_frame_filename), pt(pt)
{
}

CampBaseWindow::~CampBaseWindow() {
}

boost::optional<boost::shared_ptr<Error> > CampBaseWindow::WindowInitialize(void) {
	OPT_ERROR(WindowBase::WindowInitialize());
	unsigned int width, height;
	OPT_PAIR_UINT(width, height, DxLibWrapper::GetWindowSize());
	OPT_ERROR(Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampBaseWindow::Resize(unsigned int width, unsigned int height) {
	unsigned int w, h;
	OPT_PAIR_UINT(w, h, DxLibWrapper::GetWindowSize());
	if(w > width) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(h > height) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(w < width) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(h < height) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return WindowBase::Resize(width, height);
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type CampBaseWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event);
	switch(event->GetEventType()) {
		case EVENT_TYPE_POP_WINDOW:
		case EVENT_TYPE_NEXT_WINDOW:
			break;
		case EVENT_TYPE_KEY: {
			boost::shared_ptr<events::KeyEvent> key_event = boost::static_pointer_cast<events::KeyEvent>(event);
			if(key_event->GetAction() == events::KeyEvent::KEY_PRESS) {
				switch(key_event->GetKey()) {
					case events::KeyEvent::KEY_A:
						OPT_ERROR(RemoveThisWindow());
						break;
					case events::KeyEvent::KEY_B:
						OPT_ERROR(RemoveThisWindow());
						break;
				}
			}
			return boost::none;
		}
		default:
			// 別のWindowと併用するため、ここでイベントを握りつぶしておく
			return boost::none;
	}
	return WindowBase::NotifyEvent(event);
}

void CampBaseWindow::SendNextWindowEvent(boost::shared_ptr<Window> window) {
	boost::shared_ptr<Event> event(new events::NextWindowEvent(window));
	EventNotify::Send(event);
}

void CampBaseWindow::SendPopWindowEvent(boost::shared_ptr<Window> window) {
	boost::shared_ptr<Event> event(new events::PopWindowEvent(window));
	EventNotify::Send(event);
}


boost::optional<boost::shared_ptr<Error> > CampBaseWindow::SendNextTextWindowEvent(boost::shared_ptr<const std::string> text, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<TextWindow> window(new TextWindow(text, default_frame_filename));
	OPT_ERROR(window->Move(x, y));
	OPT_ERROR(window->Resize(width, height));
	SendNextWindowEvent(window);
	return boost::none;
}

} // windows

} // wten
