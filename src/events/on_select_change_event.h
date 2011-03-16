
namespace wten {

namespace events {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class OnSelectChangeEvent : public EventBase {
public:
	OnSelectChangeEvent(boost::shared_ptr<void> data);
	~OnSelectChangeEvent();
	boost::shared_ptr<void> GetUserData(void) const;
private:
	const boost::shared_ptr<void> data;
};
#pragma warning(pop)

} // events

} // wten
