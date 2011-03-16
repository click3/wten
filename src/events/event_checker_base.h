
namespace wten { namespace events {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class EventCheckerBase : public EventChecker {
public:
	EventCheckerBase();
	~EventCheckerBase();
	boost::optional<boost::shared_ptr<Error> > DoCheck(void) = 0;
	static boost::optional<boost::shared_ptr<Error> > SendEvent(boost::shared_ptr<Event> event);
};
#pragma warning(pop)

} // events

} // wten
