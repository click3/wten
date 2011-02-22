
namespace wten {

namespace events {

class InputStringEvent : public EventBase {
public:
	InputStringEvent(boost::shared_ptr<std::string> text);
	~InputStringEvent();
	boost::shared_ptr<std::string> GetText(void) const;
private:
	const boost::shared_ptr<std::string> text;
};

} // events

} // wten
