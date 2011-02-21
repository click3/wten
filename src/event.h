
namespace wten {

enum EVENT_TYPE {
	EVENT_TYPE_KEY,
	EVENT_TYPE_ON_SELECT,
	EVENT_TYPT_POP_WINDOW,
};

class Event : boost::noncopyable {
public:
	virtual ~Event() { }
	virtual EVENT_TYPE GetEventType(void) const = 0;
};

} // wten
