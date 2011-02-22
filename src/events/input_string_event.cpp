#include "stdafx.h"

namespace wten { namespace events {

InputStringEvent::InputStringEvent(boost::shared_ptr<std::string> text) :
	EventBase(EVENT_TYPE_INPUT_STRING), text(text)
{
	BOOST_ASSERT(text);
}

InputStringEvent::~InputStringEvent() {
}

boost::shared_ptr<std::string> InputStringEvent::GetText(void) const {
	return text;
}

} // events

} // wten
