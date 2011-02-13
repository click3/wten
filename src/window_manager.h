
namespace wten {

class Window;
class EventManager;
class Error;

class WindowManager : boost::noncopyable {
private:
	std::vector<boost::shared_ptr<Window> > window_stack;
	boost::shared_ptr<EventManager> event_manager;
public:
	WindowManager();
	boost::optional<boost::shared_ptr<Error> > Draw(void) const;
	boost::optional<boost::shared_ptr<Error> > EnqueueEvent(boost::shared_ptr<Event> event);
	boost::optional<boost::shared_ptr<Error> > DoEvent(void);
	boost::optional<boost::shared_ptr<Error> > PushWindow(boost::shared_ptr<Window> window);
	boost::optional<boost::shared_ptr<Error> > PopWindow(void);
};

} // wten
