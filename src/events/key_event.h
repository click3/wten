
namespace wten {

namespace events {

#define KEY_MAX (12)

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class KeyEvent : public EventBase {
public:
	enum ACTION {
		KEY_RELEASE,
		KEY_PRESS,
		KEY_PRESS_MORE,
	};
	enum KEY_TYPE {
		KEY_A,
		KEY_B,
		KEY_X,
		KEY_Y,
		KEY_L,
		KEY_R,
		KEY_START,
		KEY_SELECT,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
	};
	KeyEvent(ACTION action, KEY_TYPE key_type);
	~KeyEvent();
	ACTION GetAction() const;
	KEY_TYPE GetKey() const;
private:
	const ACTION action;
	const KEY_TYPE key_type;
};
#pragma warning(pop)

} // events

} // wten
