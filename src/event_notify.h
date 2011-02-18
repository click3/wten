
namespace wten {

class Event;

class EventNotifyInterface {
public:
	virtual void EventNotifyCallback(boost::shared_ptr<Event>) = 0;
};


class EventNotify {
private:
	EventNotify();
	static boost::shared_ptr<EventNotify> CreateEventNotify();
public:
	~EventNotify();
	static void Regist(boost::weak_ptr<EventNotifyInterface> ptr);
	/**
	 * “o˜^‚ğ‰ğœ‚·‚é
	 * @retval true “o˜^‚ğ‰ğœ‚µ‚½
	 * @retval false “o˜^‚³‚ê‚Ä‚¢‚È‚©‚Á‚½
	 */
	static bool UnRegist(boost::weak_ptr<EventNotifyInterface> ptr);
	static void Send(boost::shared_ptr<Event> event);

	void EventNotifyCallback(boost::shared_ptr<Event> event);
private:
	static boost::shared_ptr<EventNotify> singleton;
	const char * const event_notify_name;
	std::vector<boost::weak_ptr<EventNotifyInterface> > notifys;
	boost::shared_ptr<org::click3::NotificationCenter> notify_center;
};

} // wten
