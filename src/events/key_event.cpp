#include "stdafx.h"

namespace wten { namespace events {

KeyEvent::KeyEvent(ACTION action, KEY_TYPE key_type) :
	EventBase(EVENT_TYPE_KEY), action(action), key_type(key_type)
{
}

KeyEvent::~KeyEvent() {
}

} // events

} // wten
