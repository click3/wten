#include "stdafx.h"

namespace wten { namespace events {

KeyEvent::KeyEvent(ACTION action, KEY_TYPE key_type) :
	EventBase(EVENT_TYPE_KEY), action(action), key_type(key_type)
{
}

KeyEvent::~KeyEvent() {
}

KeyEvent::ACTION KeyEvent::GetAction() const {
	return action;
}

KeyEvent::KEY_TYPE KeyEvent::GetKey() const {
	return key_type;
}

} // events

} // wten
