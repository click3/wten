
namespace wten {

namespace events {
	
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class EventBase : public Event {
public:
	EventBase(EVENT_TYPE event_type);
	~EventBase();
	EVENT_TYPE GetEventType(void) const;
private:
	const EVENT_TYPE event_type;
};
#pragma warning(pop)

} // events

} // wten
