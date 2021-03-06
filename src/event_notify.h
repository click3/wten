
namespace wten {

class Event;

class EventNotifyInterface {
public:
	virtual void EventNotifyCallback(boost::shared_ptr<Event>) = 0;
};

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class EventNotify : boost::noncopyable {
private:
	EventNotify();
	static boost::shared_ptr<EventNotify> CreateEventNotify();
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
	const char *GetEventNotifyName(void) const;
private:
	static boost::shared_ptr<EventNotify> singleton;
	const char * const event_notify_name;
	std::vector<boost::weak_ptr<EventNotifyInterface> > notifys;
	boost::shared_ptr<org::click3::NotificationCenter> notify_center;
};
#pragma warning(pop)

} // wten
