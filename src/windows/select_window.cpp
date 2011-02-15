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

void SelectWindow::Initialize(const std::vector<boost::tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> > >& input, const boost::shared_ptr<std::string>& frame_filename) {
	boost::transform(input, std::back_inserter(data_list), TupleValues());

	std::vector<boost::shared_ptr<std::string> > select_list;
	boost::transform(input, std::back_inserter(select_list), TupleTexts());

	BOOST_ASSERT(!selector);
	selector.reset(new uis::UISelector(select_list));

	boost::optional<boost::shared_ptr<Error> > error;
	if(frame_filename && !frame_filename->empty()) {
		frame.reset(new uis::UIBox(frame_filename));
		if(error = AddUI(frame)) {
			error.get()->Abort();
			BOOST_ASSERT(false);
		}
	}
	if(error = AddUI(selector)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}


//static
boost::shared_ptr<SelectWindow> SelectWindow::CreateSelectWindow(const std::vector<boost::tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> > >& input, const boost::shared_ptr<std::string>& frame_filename) {
	boost::shared_ptr<SelectWindow> result(new SelectWindow());
	BOOST_ASSERT(result);
	result->this_ptr = result;
	BOOST_ASSERT(result->this_ptr.lock());
	result->Initialize(input, frame_filename);
	return result;
}

SelectWindow::~SelectWindow() {
}

boost::optional<boost::shared_ptr<Error> > SelectWindow::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(WindowBase::Resize(width, height));
	BOOST_ASSERT(selector);
	OPT_ERROR(selector->Resize(width, height));
	if(frame) {
		OPT_ERROR(frame->Resize(width, height));
	}
	return boost::none;
}

opt_error<boost::optional<boost::shared_ptr<Event> > >::type SelectWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event);
	if(event->GetEventType() == EVENT_TYPE_KEY) {
		BOOST_ASSERT(selector);
		boost::shared_ptr<events::KeyEvent> key = boost::static_pointer_cast<events::KeyEvent>(event);
		if(key->GetAction() == events::KeyEvent::KEY_PRESS) {
			switch(key->GetKey()) {
				case events::KeyEvent::KEY_UP:
					OPT_ERROR(selector->Select(uis::UISelector::MOVE_FOCUS_UP));
					return boost::none;
				case events::KeyEvent::KEY_DOWN:
					OPT_ERROR(selector->Select(uis::UISelector::MOVE_FOCUS_DOWN));
					return boost::none;
				case events::KeyEvent::KEY_A:
					OPT_ERROR(OnSelect());
					return boost::none;
			}
		}
	}
	return event;
}


boost::optional<boost::shared_ptr<Error> > SelectWindow::OnSelect(void) {
	BOOST_ASSERT(selector);
	unsigned int index;
	OPT_UINT(index, selector->GetIndex());
	BOOST_ASSERT(!data_list.empty());
	BOOST_ASSERT(index < data_list.size());
	boost::shared_ptr<void> data = data_list[index];
	boost::shared_ptr<Event> event(new events::OnSelectEvent(data));
	BOOST_ASSERT(event);
	EventNotify::Send(event);
	return boost::none;
}

} // windows

} // wten
