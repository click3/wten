
namespace wten {

namespace events {

class EventBase : public Event {
public:
	EventBase(EVENT_TYPE event_type);
	~EventBase();
	EVENT_TYPE GetEventType(void);
	void SetEventType(EVENT_TYPE event_type);
private:
	EVENT_TYPE event_type;
};

} // events

} // wten
