#include "stdafx.h"

namespace wten {

namespace windows {

namespace {

struct TupleValues {
	boost::shared_ptr<void> operator ()(const boost::tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> >& data) {
		return data.get<1>();
	}
};

struct TupleTexts {
	boost::shared_ptr<std::string> operator ()(const boost::tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> >& data) {
		return data.get<0>();
	}
};

} // anonymous

using namespace utility;

SelectWindow::SelectWindow() {
}

//static
boost::shared_ptr<SelectWindow> SelectWindow::CreateSelectWindow(const std::vector<boost::tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> > >& input) {
	boost::shared_ptr<SelectWindow> result(new SelectWindow());
	BOOST_ASSERT(result);
	result->this_ptr = result;
	BOOST_ASSERT(result->this_ptr.lock());

	boost::transform(input, std::back_inserter(result->data_list), TupleValues());

	std::vector<boost::shared_ptr<std::string> > select_list;
	boost::transform(input, std::back_inserter(select_list), TupleTexts());

	BOOST_ASSERT(!result->selector);
	result->selector.reset(new uis::UISelector(select_list));

	boost::optional<boost::shared_ptr<Error> > error = result->AddUI(result->selector);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	return result;
}

SelectWindow::~SelectWindow() {
}

boost::optional<boost::shared_ptr<Error> > SelectWindow::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(WindowBase::Resize(width, height));
	BOOST_ASSERT(selector);
	OPT_ERROR(selector->Resize(width, height));
	return boost::none;
}

opt_error<boost::optional<boost::shared_ptr<Event> > >::type SelectWindow::NotifyEvent(boost::shared_ptr<Event> event) {
printf("event start\n");
	BOOST_ASSERT(event);
	if(event->GetEventType() != EVENT_TYPE_KEY) {
		return event;
	}
	BOOST_ASSERT(selector);
	boost::shared_ptr<events::KeyEvent> key = boost::static_pointer_cast<events::KeyEvent>(event);
	if(key->GetAction() == events::KeyEvent::KEY_PRESS) {
		switch(key->GetKey()) {
			case events::KeyEvent::KEY_UP:
				OPT_ERROR(selector->Select(uis::UISelector::MOVE_FOCUS_UP));
				break;
			case events::KeyEvent::KEY_DOWN:
				OPT_ERROR(selector->Select(uis::UISelector::MOVE_FOCUS_DOWN));
				break;
		}
	}
	return boost::none;
}

} // windows

} // wten
