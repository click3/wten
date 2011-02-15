
namespace wten {

namespace events {

#define KEY_MAX (12)

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
	ACTION action;
	KEY_TYPE key_type;
};

} // events

} // wten
