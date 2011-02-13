#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace org::click3;

namespace {

void EventNotifyCallbackProxy(const char *notify_name, boost::shared_ptr<void> user_data, boost::shared_ptr<void> data) {
	boost::shared_ptr<EventNotify> owner = boost::static_pointer_cast<EventNotify>(user_data);
	boost::shared_ptr<Event> event = boost::static_pointer_cast<Event>(data);
	owner->EventNotifyCallback(event);
}

struct EqualByPtrAddress {
	EqualByPtrAddress(boost::weak_ptr<EventNotifyInterface> ptr) : ptr(ptr) { }
	bool operator()(boost::weak_ptr<EventNotifyInterface> obj) const {
		return ptr.lock() == obj.lock();
	}
	boost::weak_ptr<EventNotifyInterface> ptr;
};

} // anonymous

EventNotify::EventNotify() :
	event_notify_name("WTEN_EVENT_NOTIFY_NAME")
{
	BOOST_ASSERT(!singleton);

	boost::shared_ptr<NotificationCenter> center = NotificationCenter::GetDefaultCenter();
	BOOST_ASSERT(center);
	boost::shared_ptr<void> user_data(this);
	center->AddObserver(event_notify_name, &EventNotifyCallbackProxy, user_data);
}

EventNotify::~EventNotify() {
	boost::shared_ptr<NotificationCenter> center = NotificationCenter::GetDefaultCenter();
	BOOST_ASSERT(center);
	BOOST_ASSERT(center->RemoveObserver(event_notify_name, &EventNotifyCallbackProxy));
}

//static
void EventNotify::Regist(boost::weak_ptr<EventNotifyInterface> ptr) {
	if(!singleton) {
		singleton.reset(new EventNotify());
		BOOST_ASSERT(singleton);
	}
	singleton->notifys.push_back(ptr);
}

//static
bool EventNotify::UnRegist(boost::weak_ptr<EventNotifyInterface> ptr) {
	if(!singleton) {
		return false;
	}
	std::vector<boost::weak_ptr<EventNotifyInterface> >::iterator it = std::find_if(singleton->notifys.begin(), singleton->notifys.end(), EqualByPtrAddress(ptr));
	if(it == singleton->notifys.end()) {
		return false;
	}
	singleton->notifys.erase(it);
	return true;
}

//static
void EventNotify::Send(boost::shared_ptr<Event> event) {
	if(!singleton) {
		return;
	}
	boost::shared_ptr<NotificationCenter> center = NotificationCenter::GetDefaultCenter();
	BOOST_ASSERT(center);
	boost::shared_ptr<void> data = event;
	center->SendNotification(singleton->event_notify_name, data);
}

void EventNotify::EventNotifyCallback(boost::shared_ptr<Event> event) {
	BOOST_FOREACH(boost::weak_ptr<EventNotifyInterface> weak, notifys) {
		if(boost::shared_ptr<EventNotifyInterface> ptr = weak.lock()) {
			ptr->EventNotifyCallback(event);
		}
	}
}

boost::shared_ptr<EventNotify> EventNotify::singleton;

} // wten
