#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;
using namespace boost::assign;

TextWindow::TextWindow(boost::shared_ptr<const std::string> text, boost::shared_ptr<const std::string> frame_filename) :
	WindowBase(frame_filename), ui_string(new uis::UIString(text)), frame(new uis::UIBox(boost::shared_ptr<Graph>(new Graph(frame_filename))))
{
	BOOST_ASSERT(ui_string);
	BOOST_ASSERT(frame_filename);
	BOOST_ASSERT(!frame_filename->empty());
	BOOST_ASSERT(frame);
	boost::optional<boost::shared_ptr<Error> > error = this->frame->SetInnerUI(ui_string);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

TextWindow::TextWindow(boost::shared_ptr<const std::string> text, boost::shared_ptr<Graph> frame) :
	ui_string(new uis::UIString(text)), frame(new uis::UIBox(frame))
{
	BOOST_ASSERT(ui_string);
	BOOST_ASSERT(frame);
	boost::optional<boost::shared_ptr<Error> > error = this->frame->SetInnerUI(ui_string);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

TextWindow::TextWindow(boost::shared_ptr<const std::string> text) :
	ui_string(new uis::UIString(text))
{
	BOOST_ASSERT(ui_string);
	BOOST_ASSERT(!frame);
}

TextWindow::~TextWindow() {
}

boost::optional<boost::shared_ptr<Error> > TextWindow::WindowInitialize(void) {
	OPT_ERROR(WindowBase::WindowInitialize());
	if(frame) {
		OPT_ERROR(AddUI(frame));
	} else {
		OPT_ERROR(AddUI(ui_string));
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TextWindow::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(WindowBase::Resize(width, height));
	if(frame) {
		OPT_ERROR(frame->Resize(width, height));
	} else {
		OPT_ERROR(ui_string->Resize(width, height));
	}
	return boost::none;
}

opt_error<boost::optional<boost::shared_ptr<Event> > >::type TextWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event);
	if(event->GetEventType() == EVENT_TYPE_KEY) {
		boost::shared_ptr<events::KeyEvent> key = boost::static_pointer_cast<events::KeyEvent>(event);
		if(key->GetAction() == events::KeyEvent::KEY_PRESS) {
			switch(key->GetKey()) {
				case events::KeyEvent::KEY_A:
					OPT_ERROR(OnOK());
					return boost::none;
			}
		}
	}
	return event;
}

boost::optional<boost::shared_ptr<Error> > TextWindow::OnOK(void) {
	boost::shared_ptr<Event> event(new events::NextStepEvent());
	OPT_ERROR(RemoveThisWindow());
	EventNotify::Send(event);
	return boost::none;
}

} // windows

} // wten
