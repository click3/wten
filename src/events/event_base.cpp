#include "stdafx.h"

namespace wten { namespace events {

using namespace utility;

EventBase::EventBase(EVENT_TYPE event_type) :
	event_type(event_type)
{
}

EventBase::~EventBase() {
}

opt_error<EVENT_TYPE>::type EventBase::GetEventType(void) {
	return event_type;
}

boost::optional<boost::shared_ptr<Error> > EventBase::SetEventType(EVENT_TYPE event_type) {
	this->event_type = event_type;
	return boost::none;
}

} // events

} // wten
