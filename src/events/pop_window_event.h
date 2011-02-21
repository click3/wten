
namespace wten {

class Window;

namespace events {

class PopWindowEvent : public EventBase {
public:
	PopWindowEvent(boost::shared_ptr<Window> window);
	~PopWindowEvent();
	boost::shared_ptr<Window> GetWindow(void) const;
private:
	const boost::shared_ptr<Window> window;
};

} // events

} // wten
