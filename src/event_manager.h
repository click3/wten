
namespace wten {

class Event;
class Error;

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class EventManager : boost::noncopyable {
public:
	EventManager();
	boost::optional<boost::shared_ptr<Error> > DoCheck(void);
	boost::optional<boost::shared_ptr<Error> > Enqueue(boost::shared_ptr<Event> event);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type Dequeue(void);
	boost::optional<boost::shared_ptr<Error> > Clear(void);
protected:
	std::queue<boost::shared_ptr<Event> > event_queue;
	std::vector<boost::shared_ptr<EventChecker> > checker_list;
};
#pragma warning(pop)

} // wten
