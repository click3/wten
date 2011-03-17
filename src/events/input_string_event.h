
namespace wten {

namespace events {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class InputStringEvent : public EventBase {
public:
	InputStringEvent(boost::shared_ptr<std::wstring> text);
	~InputStringEvent();
	boost::shared_ptr<std::wstring> GetText(void) const;
private:
	const boost::shared_ptr<std::wstring> text;
};
#pragma warning(pop)

} // events

} // wten
