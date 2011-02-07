#include "stdafx.h"

namespace wten {

using namespace utility;

boost::optional<boost::shared_ptr<Error> > EventManager::Enqueue(boost::shared_ptr<Event> event) {
	event_queue.push(event);
	return boost::none;
}

opt_error<boost::optional<boost::shared_ptr<Event> > >::type EventManager::Dequeue(void) {
	if(event_queue.empty()) {
		return boost::none;
	}
	boost::shared_ptr<Event> result = event_queue.front();
	event_queue.pop();
	return result;
}

} // wten
