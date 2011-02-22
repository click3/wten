#include "stdafx.h"

namespace wten { namespace events {

OnSelectChangeEvent::OnSelectChangeEvent(boost::shared_ptr<void> data) :
	EventBase(EVENT_TYPE_ON_SELECT_CHANGE), data(data)
{
}

OnSelectChangeEvent::~OnSelectChangeEvent() {
}

boost::shared_ptr<void> OnSelectChangeEvent::GetUserData(void) const {
	return data;
}

} // events

} // wten
