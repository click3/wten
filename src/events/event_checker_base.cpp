#include "stdafx.h"

namespace wten { namespace events {

EventCheckerBase::EventCheckerBase() {
}

EventCheckerBase::~EventCheckerBase() {
}

boost::optional<boost::shared_ptr<Error> > EventCheckerBase::SendEvent(boost::shared_ptr<Event> event) {
	EventNotify::Send(event);
	return boost::none;
}

} // events

} // wten
