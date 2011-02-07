
namespace wten {

class Event;
class Error;

class EventManager : boost::noncopyable {
private:
	std::queue<boost::shared_ptr<Event> > event_queue;
public:
	boost::optional<boost::shared_ptr<Error> > Enqueue(boost::shared_ptr<Event> event);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type Dequeue(void);
};

} // wten
