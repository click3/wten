#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;

namespace {

typedef std::pair<EVENT_TYPE, boost::function<boost::optional<boost::shared_ptr<Error> > (boost::shared_ptr<Event>)> > PROC_PAIR;
typedef std::multimap<EVENT_TYPE, boost::function<boost::optional<boost::shared_ptr<Error> > (boost::shared_ptr<Event>)> >::iterator PROC_ITERATOR;

} // anonymous

ScriptWindow::ScriptWindow() {
}

ScriptWindow::~ScriptWindow() {
}

boost::optional<boost::shared_ptr<Error> > ScriptWindow::WindowInitialize(void) {
	return WindowBase::WindowInitialize();
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type ScriptWindow::GetPoint(void) const {
	return boost::make_tuple<unsigned int, unsigned int>(0, 0);
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type ScriptWindow::GetSize(void) const {
	return boost::make_tuple<unsigned int, unsigned int>(0, 0);
}

boost::optional<boost::shared_ptr<Error> > ScriptWindow::Move(unsigned int, unsigned int) {
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > ScriptWindow::Resize(unsigned int, unsigned int) {
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > ScriptWindow::Draw(void) {
	return boost::none;
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type ScriptWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event);
	std::pair<PROC_ITERATOR, PROC_ITERATOR> its = proc_list.equal_range(event->GetEventType());
	for(; its.first != its.second; its.first++) {
		OPT_ERROR(its.first->second(event));
	}
	return event;
}

boost::optional<boost::shared_ptr<Error> > ScriptWindow::AddEventProc(EVENT_TYPE event_type, boost::function<boost::optional<boost::shared_ptr<Error> > (boost::shared_ptr<Event>)> proc) {
	proc_list.insert(PROC_PAIR(event_type, proc));
	return boost::none;
}

} // windows

} // wten
