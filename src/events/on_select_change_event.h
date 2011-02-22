
namespace wten {

namespace events {

class OnSelectChangeEvent : public EventBase {
public:
	OnSelectChangeEvent(boost::shared_ptr<void> data);
	~OnSelectChangeEvent();
	boost::shared_ptr<void> GetUserData(void) const;
private:
	const boost::shared_ptr<void> data;
};

} // events

} // wten
