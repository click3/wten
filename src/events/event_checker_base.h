
namespace wten { namespace events {

class EventCheckerBase : public EventChecker {
public:
	EventCheckerBase();
	~EventCheckerBase();
	boost::optional<boost::shared_ptr<Error> > DoCheck(void) = 0;
protected:
	boost::optional<boost::shared_ptr<Error> > SendEvent(boost::shared_ptr<Event> event);
};

} // events

} // wten
