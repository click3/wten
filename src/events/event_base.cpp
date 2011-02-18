#include "stdafx.h"

namespace wten { namespace events {

using namespace utility;

EventBase::EventBase(EVENT_TYPE event_type) :
	event_type(event_type)
{
}

EventBase::~EventBase() {
}

EVENT_TYPE EventBase::GetEventType(void) const {
	return event_type;
}

} // events

} // wten
