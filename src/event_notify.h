
namespace wten {

class Event;

class EventNotifyInterface {
public:
	virtual void EventNotifyCallback(boost::shared_ptr<Event>) = 0;
};


class EventNotify {
private:
	EventNotify();
public:
	~EventNotify();
	static void Regist(boost::weak_ptr<EventNotifyInterface> ptr);
	/**
	 * 登録を解除する
	 * @retval true 登録を解除した
	 * @retval false 登録されていなかった
	 */
	static bool UnRegist(boost::weak_ptr<EventNotifyInterface> ptr);
	static void Send(boost::shared_ptr<Event> event);

	void EventNotifyCallback(boost::shared_ptr<Event> event);
private:
	static boost::shared_ptr<EventNotify> singleton;
	const char *event_notify_name;
	std::vector<boost::weak_ptr<EventNotifyInterface> > notifys;
};

} // wten
