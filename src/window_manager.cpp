#include "stdafx.h"

namespace wten {

using namespace utility;

#define OPT_EVENT(out, in)	OPT_VALUE(out, in, boost::optional<boost::shared_ptr<Event> >)

WindowManager::WindowManager() :
	event_manager(new EventManager())
{
}

boost::optional<boost::shared_ptr<Error> > WindowManager::Draw(void) const {
	BOOST_FOREACH(boost::shared_ptr<Window> window, window_stack) {
		OPT_ERROR(window->Draw());
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowManager::EnqueueEvent(boost::shared_ptr<Event> event) {
	return event_manager->Enqueue(event);
}

boost::optional<boost::shared_ptr<Error> > WindowManager::DoEvent(void) {
	OPT_ERROR(event_manager->DoCheck());
	while(true) {
		boost::optional<boost::shared_ptr<Event> > event;
		OPT_EVENT(event, event_manager->Dequeue());
		if(!event) {
			break;
		}
		BOOST_REVERSE_FOREACH(boost::shared_ptr<Window> window, window_stack) {
			boost::optional<boost::shared_ptr<Event> > next_event;
			OPT_EVENT(next_event, window->NotifyEvent(event.get()));
			if(!next_event) {
				break;
			}
			event = next_event;
		}
		if(event) {
			OPT_ERROR(ManageEventProcedure(event.get()));
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowManager::ManageEventProcedure(boost::shared_ptr<Event> event) {
	if(!event) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	switch(event->GetEventType()) {
		case EVENT_TYPE_POP_WINDOW:
			return PopWindowEvent(event);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowManager::PushWindow(boost::shared_ptr<Window> window) {
	window_stack.push_back(window);
	return window->WindowInitialize();
}

boost::optional<boost::shared_ptr<Error> > WindowManager::PopWindow(void) {
	window_stack.pop_back();
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowManager::PopWindowEvent(boost::shared_ptr<Event> event) {
	if(!event) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(event->GetEventType() != EVENT_TYPE_POP_WINDOW) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	boost::shared_ptr<events::PopWindowEvent> pop_event = boost::static_pointer_cast<events::PopWindowEvent>(event);
	boost::shared_ptr<Window> window = pop_event->GetWindow();
	BOOST_ASSERT(window);
	if(window_stack.empty() || window_stack.back() != window) {
		return CREATE_ERROR(ERROR_CODE_POP_WINDOW_INVALID_WINDOW);
	}
	return PopWindow();
}

boost::optional<boost::shared_ptr<Error> > WindowManager::Clear(void) {
	window_stack.clear();
	return event_manager->Clear();
}

} // wten
