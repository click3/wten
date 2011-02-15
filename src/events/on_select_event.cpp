#include "stdafx.h"

namespace wten { namespace events {

OnSelectEvent::OnSelectEvent(boost::shared_ptr<void> data) :
	EventBase(EVENT_TYPE_ON_SELECT), data(data)
{
}

OnSelectEvent::~OnSelectEvent() {
}

boost::shared_ptr<void> OnSelectEvent::GetUserData(void) {
	return data;
}

} // events

} // wten
