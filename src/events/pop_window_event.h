
namespace wten {

class Window;

namespace events {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class PopWindowEvent : public EventBase {
public:
	PopWindowEvent(boost::shared_ptr<Window> window);
	~PopWindowEvent();
	boost::shared_ptr<Window> GetWindow(void) const;
private:
	const boost::shared_ptr<Window> window;
};
#pragma warning(pop)

} // events

} // wten
