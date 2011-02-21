#include "stdafx.h"

namespace wten { namespace events {

PopWindowEvent::PopWindowEvent(boost::shared_ptr<Window> window) :
	EventBase(EVENT_TYPT_POP_WINDOW), window(window)
{
	BOOST_ASSERT(window);
}

PopWindowEvent::~PopWindowEvent() {
}

boost::shared_ptr<Window> PopWindowEvent::GetWindow(void) const {
	return window;
}

} // events

} // wten
