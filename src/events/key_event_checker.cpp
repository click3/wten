#include "stdafx.h"

namespace wten { namespace events {

using namespace utility;

namespace {

boost::optional<boost::shared_ptr<Error> > SendKeyEvent(KeyEvent::ACTION action, KeyEvent::KEY_TYPE key_type) {
	boost::shared_ptr<KeyEvent> event(new KeyEvent(action, key_type));
	BOOST_ASSERT(event);
	return KeyEventChecker::SendEvent(event);
}

struct KeyMap {
	KeyEvent::KEY_TYPE WTenKey;
	int DxLibKey;
};

} // anonymous

KeyEventChecker::KeyEventChecker() {
}

KeyEventChecker::~KeyEventChecker() {
}

boost::optional<boost::shared_ptr<Error> > KeyEventChecker::DoCheck(void) {
	unsigned int key_state;
	OPT_UINT(key_state, DxLibWrapper::GetJoypadInputState());

	const KeyMap key_map[KEY_MAX] = {
		{KeyEvent::KEY_A,	PAD_INPUT_B},	{KeyEvent::KEY_B,	PAD_INPUT_C},		{KeyEvent::KEY_X,		PAD_INPUT_A},		{KeyEvent::KEY_Y,		PAD_INPUT_X},
		{KeyEvent::KEY_L,	PAD_INPUT_L},	{KeyEvent::KEY_R,	PAD_INPUT_R},		{KeyEvent::KEY_START,	PAD_INPUT_START},	{KeyEvent::KEY_SELECT,	PAD_INPUT_M},
		{KeyEvent::KEY_UP,	PAD_INPUT_UP},{KeyEvent::KEY_DOWN,	PAD_INPUT_DOWN},	{KeyEvent::KEY_LEFT,		PAD_INPUT_LEFT},	{KeyEvent::KEY_RIGHT,	PAD_INPUT_RIGHT}
	};

	BOOST_FOREACH(KeyMap key, key_map) {
		const KeyEvent::ACTION act = (key_state & key.DxLibKey) ? KeyEvent::KEY_PRESS : KeyEvent::KEY_RELEASE;
		if(!prev[key.WTenKey]) {
			prev[key.WTenKey] = act;
		} else if(prev[key.WTenKey] != act) {
			prev[key.WTenKey] = act;
			press_frame[key.WTenKey] = 0;
			OPT_ERROR(SendKeyEvent(act, key.WTenKey));
		} else if(act == KeyEvent::KEY_PRESS) {
			press_frame[key.WTenKey]++;
			if(press_frame[key.WTenKey] > 20 && (press_frame[key.WTenKey]%2) == 0) {
				OPT_ERROR(SendKeyEvent(KeyEvent::KEY_PRESS_MORE, key.WTenKey));
			}
		}
	}
	return boost::none;
}

} // events

} // wten
