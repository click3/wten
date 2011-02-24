
namespace wten {

namespace events {

class NextWindowEvent : public EventBase {
public:
	NextWindowEvent(boost::shared_ptr<Window> window);
	~NextWindowEvent();
	boost::shared_ptr<Window> GetWindow(void) const;
private:
	const boost::shared_ptr<Window> window;
};

} // events

} // wten
