
namespace wten {

enum EVENT_TYPE {
	EVENT_TYPE_KEY,
};

class Event : boost::noncopyable {
public:
	virtual ~Event() { }
	virtual EVENT_TYPE GetEventType(void) = 0;
};

} // wten
