
namespace wten {

namespace events {

class EventBase : public Event {
public:
	EventBase(EVENT_TYPE event_type);
	~EventBase();
	utility::opt_error<EVENT_TYPE>::type GetEventType(void);
	boost::optional<boost::shared_ptr<Error> > SetEventType(EVENT_TYPE event_type);
private:
	EVENT_TYPE event_type;
};

} // events

} // wten
