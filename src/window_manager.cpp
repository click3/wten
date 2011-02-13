#include "stdafx.h"

namespace wten {

using namespace utility;

WindowManager::WindowManager() :
	event_manager(new EventManager())
{
}

boost::optional<boost::shared_ptr<Error> > WindowManager::Draw(void) const {
	BOOST_FOREACH(boost::shared_ptr<Window> window, window_stack) {
		boost::optional<boost::shared_ptr<Error> > error = window->Draw();
		if(error) {
			return error;
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowManager::EnqueueEvent(boost::shared_ptr<Event> event) {
	return event_manager->Enqueue(event);
}

boost::optional<boost::shared_ptr<Error> > WindowManager::DoEvent(void) {
	while(true) {
		opt_error<boost::optional<boost::shared_ptr<Event> > >::type event_opt = event_manager->Dequeue();
		if(event_opt.which() == 0) {
			boost::shared_ptr<Error> error = boost::get<boost::shared_ptr<Error> >(event_opt);
			return error;
		}
		boost::optional<boost::shared_ptr<Event> > event = boost::get<boost::optional<boost::shared_ptr<Event> > >(event_opt);
		if(!event) {
			break;
		}
		BOOST_REVERSE_FOREACH(boost::shared_ptr<Window> window, window_stack) {
			opt_error<boost::optional<boost::shared_ptr<Event> > >::type result = window->NotifyEvent(event.get());
			if(result.which() == 1) {
				boost::shared_ptr<Error> error = boost::get<boost::shared_ptr<Error> >(result);
				return error;
			}
			boost::optional<boost::shared_ptr<Event> > next_event = boost::get<boost::optional<boost::shared_ptr<Event> > >(result);
			if(!next_event) {
				break;
			}
			event = next_event;
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowManager::PushWindow(boost::shared_ptr<Window> window) {
	window_stack.push_back(window);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowManager::PopWindow(void) {
	window_stack.pop_back();
	return boost::none;
}

} // wten
