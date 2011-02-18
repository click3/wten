
namespace wten {

namespace events {

class OnSelectEvent : public EventBase {
public:
	OnSelectEvent(boost::shared_ptr<void> data);
	~OnSelectEvent();
	boost::shared_ptr<void> GetUserData(void) const;
private:
	const boost::shared_ptr<void> data;
};

} // events

} // wten
