#include "stdafx.h"

namespace wten { namespace events {

NextWindowEvent::NextWindowEvent(boost::shared_ptr<Window> window) :
	EventBase(EVENT_TYPE_NEXT_WINDOW), window(window)
{
	BOOST_ASSERT(window);
}

NextWindowEvent::~NextWindowEvent() {
}

boost::shared_ptr<Window> NextWindowEvent::GetWindow(void) const {
	return window;
}

} // events

} // wten
