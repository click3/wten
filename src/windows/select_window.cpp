#include "stdafx.h"

namespace wten {

namespace windows {

namespace {

struct TupleValues {
	boost::shared_ptr<void> operator ()(const boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> >& data) {
		return data.get<1>();
	}
};

struct TupleTexts {
	boost::shared_ptr<const std::string> operator ()(const boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> >& data) {
		return data.get<0>();
	}
};

std::vector<boost::shared_ptr<const std::string> > CreateSelectList(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input) {
	std::vector<boost::shared_ptr<const std::string> > result;
	boost::transform(input, std::back_inserter(result), TupleTexts());
	return result;
}

std::vector<boost::shared_ptr<void> > CreateDataList(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input) {
	std::vector<boost::shared_ptr<void> > result;
	boost::transform(input, std::back_inserter(result), TupleValues());
	return result;
}

} // anonymous

using namespace utility;

SelectWindow::SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input, boost::shared_ptr<const std::string> frame_filename) :
	WindowBase(frame_filename),
	selector(new uis::UISelector(CreateSelectList(input))),
	data_list(CreateDataList(input)),
	frame(new uis::UIBox(frame_filename)),
	select_close(true)
{
	BOOST_ASSERT(selector);
	BOOST_ASSERT(selector->GetCount() == data_list.size());
	BOOST_ASSERT(frame_filename);
	BOOST_ASSERT(!frame_filename->empty());
	BOOST_ASSERT(frame);
}

SelectWindow::SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input, boost::shared_ptr<Graph> frame) :
	selector(new uis::UISelector(CreateSelectList(input))), data_list(CreateDataList(input)), frame(new uis::UIBox(frame)), select_close(true)
{
	BOOST_ASSERT(selector);
	BOOST_ASSERT(selector->GetCount() == data_list.size());
	BOOST_ASSERT(frame);
}

SelectWindow::SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input) :
	selector(new uis::UISelector(CreateSelectList(input))), data_list(CreateDataList(input)), select_close(true)
{
	BOOST_ASSERT(selector);
	BOOST_ASSERT(selector->GetCount() == data_list.size());
	BOOST_ASSERT(!frame);
}

SelectWindow::~SelectWindow() {
}

bool SelectWindow::IsSelectClose(void) const {
	return select_close;
}

void SelectWindow::SetSelectClose(bool flag) {
	select_close = flag;
}

boost::optional<boost::shared_ptr<Error> > SelectWindow::WindowInitialize(void) {
	OPT_ERROR(WindowBase::WindowInitialize());
	if(frame) {
		OPT_ERROR(AddUI(frame));
	}
	OPT_ERROR(AddUI(selector));
	return boost::none;
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
					OPT_ERROR(OnSelectChange());
					return boost::none;
				case events::KeyEvent::KEY_DOWN:
					OPT_ERROR(selector->Select(uis::UISelector::MOVE_FOCUS_DOWN));
					OPT_ERROR(OnSelectChange());
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
	BOOST_ASSERT(index < data_list.size());
	boost::shared_ptr<void> data = data_list[index];
	boost::shared_ptr<Event> event(new events::OnSelectEvent(data));
	if(select_close) {
		OPT_ERROR(RemoveThisWindow());
	}
	EventNotify::Send(event);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > SelectWindow::OnSelectChange(void) {
	BOOST_ASSERT(selector);
	unsigned int index;
	OPT_UINT(index, selector->GetIndex());
	BOOST_ASSERT(index < data_list.size());
	boost::shared_ptr<void> data = data_list[index];
	boost::shared_ptr<Event> event(new events::OnSelectChangeEvent(data));
	EventNotify::Send(event);
	return boost::none;
}

} // windows

} // wten
