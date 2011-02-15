
namespace wten {

enum EVENT_TYPE {
	EVENT_TYPE_KEY,
};

class Event : boost::noncopyable {
public:
	virtual ~Event() { }
	virtual utility::opt_error<EVENT_TYPE>::type GetEventType(void) = 0;
};

} // wten
