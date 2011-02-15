#include "stdafx.h"

namespace wten { namespace events {

using namespace utility;

EventBase::EventBase(EVENT_TYPE event_type) :
	event_type(event_type)
{
}

EventBase::~EventBase() {
}

EVENT_TYPE EventBase::GetEventType(void) {
	return event_type;
}

void EventBase::SetEventType(EVENT_TYPE event_type) {
	this->event_type = event_type;
}

} // events

} // wten
