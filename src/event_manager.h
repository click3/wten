
namespace wten {

class Event;
class Error;

class EventManager : boost::noncopyable {
private:
	std::queue<boost::shared_ptr<Event> > event_queue;
public:
	EventManager();
	boost::optional<boost::shared_ptr<Error> > DoCheck(void);
	boost::optional<boost::shared_ptr<Error> > Enqueue(boost::shared_ptr<Event> event);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type Dequeue(void);
protected:
	std::vector<boost::shared_ptr<EventChecker> > checker_list;
};

} // wten
