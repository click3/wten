#include "stdafx.h"

namespace wten { namespace events {

NextStepEvent::NextStepEvent() :
	EventBase(EVENT_TYPE_NEXT_STEP)
{
}

NextStepEvent::~NextStepEvent() {
}

} // events

} // wten
