
namespace wten {

namespace events {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class InputStringEvent : public EventBase {
public:
	InputStringEvent(boost::shared_ptr<std::string> text);
	~InputStringEvent();
	boost::shared_ptr<std::string> GetText(void) const;
private:
	const boost::shared_ptr<std::string> text;
};
#pragma warning(pop)

} // events

} // wten
