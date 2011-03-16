
namespace wten {

namespace events {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class NextWindowEvent : public EventBase {
public:
	NextWindowEvent(boost::shared_ptr<Window> window);
	~NextWindowEvent();
	boost::shared_ptr<Window> GetWindow(void) const;
private:
	const boost::shared_ptr<Window> window;
};
#pragma warning(pop)

} // events

} // wten
