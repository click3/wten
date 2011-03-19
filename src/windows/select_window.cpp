#include "stdafx.h"

namespace wten {

namespace windows {

namespace {

struct TupleValues {
	boost::shared_ptr<void> operator ()(const boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> >& data) {
		return data.get<1>();
	}
};

struct TupleTexts {
	boost::shared_ptr<const std::wstring> operator ()(const boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> >& data) {
		return data.get<0>();
	}
};

std::vector<boost::shared_ptr<const std::wstring> > CreateSelectList(const std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > >& input) {
	std::vector<boost::shared_ptr<const std::wstring> > result;
	boost::transform(input, std::back_inserter(result), TupleTexts());
	return result;
}

std::vector<boost::shared_ptr<void> > CreateDataList(const std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > >& input) {
	std::vector<boost::shared_ptr<void> > result;
	boost::transform(input, std::back_inserter(result), TupleValues());
	return result;
}

} // anonymous

using namespace utility;

SelectWindow::SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > >& input, unsigned int line_count, boost::shared_ptr<const std::wstring> frame_filename) :
	WindowBase(frame_filename),
	selector(new uis::UISelector(CreateSelectList(input), line_count)),
	data_list(CreateDataList(input)),
	frame(new uis::UIBox(frame_filename)),
	select_close(true),
	cancel_data_index(boost::none)
{
	BOOST_ASSERT(selector);
	BOOST_ASSERT(selector->GetCount() == data_list.size());
	BOOST_ASSERT(frame_filename);
	BOOST_ASSERT(!frame_filename->empty());
	BOOST_ASSERT(frame);
}

SelectWindow::SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > >& input, unsigned int line_count, boost::shared_ptr<Graph> frame) :
	selector(new uis::UISelector(CreateSelectList(input), line_count)), data_list(CreateDataList(input)), frame(new uis::UIBox(frame)), select_close(true), cancel_data_index(boost::none)
{
	BOOST_ASSERT(selector);
	BOOST_ASSERT(selector->GetCount() == data_list.size());
	BOOST_ASSERT(frame);
}

SelectWindow::SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > >& input, unsigned int line_count) :
	selector(new uis::UISelector(CreateSelectList(input), line_count)), data_list(CreateDataList(input)), select_close(true), cancel_data_index(boost::none)
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

boost::optional<boost::shared_ptr<Error> > SelectWindow::SetCancelSelectionDataIndex(boost::optional<unsigned int> cancel_data_index) {
	if(cancel_data_index && cancel_data_index.get() >= data_list.size()) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	this->cancel_data_index = cancel_data_index;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > SelectWindow::SetCancelSelectionDataIndex(boost::shared_ptr<void> data) {
	const std::vector<boost::shared_ptr<void> >::const_iterator it = std::find(data_list.begin(), data_list.end(), data);
	if(it == data_list.end()) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	const int index = std::distance(data_list.begin(), it);
	if(index < 0) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return SetCancelSelectionDataIndex(static_cast<unsigned int>(index));
}

boost::optional<boost::shared_ptr<Error> > SelectWindow::SetCancelSelectionDataIndex(boost::shared_ptr<const std::wstring> text) {
	unsigned int current_index;
	OPT_UINT(current_index, selector->GetIndex());
	OPT_ERROR(selector->Select(text));
	unsigned int cancel_data_index;
	OPT_UINT(cancel_data_index, selector->GetIndex());
	OPT_ERROR(selector->Select(current_index));
	return SetCancelSelectionDataIndex(cancel_data_index);
}

boost::optional<boost::shared_ptr<Error> > SelectWindow::WindowInitialize(void) {
	OPT_ERROR(WindowBase::WindowInitialize());
	if(frame) {
		OPT_ERROR(AddUI(frame));
	}
	OPT_ERROR(AddUI(selector));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > SelectWindow::Resize() {
	unsigned int width, height;
	OPT_ERROR(selector->Resize());
	OPT_PAIR_UINT(width, height, selector->GetSize());
	if(frame) {
		unsigned int frame_w, frame_h;
		OPT_ERROR(frame->Resize());
		OPT_PAIR_UINT(frame_w, frame_h, frame->GetSize());
		width += frame_w;
		height += frame_h;
	}
	return Resize(width, height);
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
				case events::KeyEvent::KEY_RIGHT:
					OPT_ERROR(selector->Select(uis::UISelector::MOVE_FOCUS_RIGHT));
					OPT_ERROR(OnSelectChange());
					return boost::none;
				case events::KeyEvent::KEY_LEFT:
					OPT_ERROR(selector->Select(uis::UISelector::MOVE_FOCUS_LEFT));
					OPT_ERROR(OnSelectChange());
					return boost::none;
				case events::KeyEvent::KEY_A:
					OPT_ERROR(OnSelect());
					return boost::none;
				case events::KeyEvent::KEY_B:
					if(cancel_data_index) {
						OPT_ERROR(selector->Select(cancel_data_index.get()));
						OPT_ERROR(OnSelect());
						return boost::none;
					}
					//cancel_data_indexÇ™ñ¢ê›íËÇ»èÍçáÇÕå„ë±ÇÃwindowÇ…ÉCÉxÉìÉgÇó¨Ç∑
					break;
				default:
					break;
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
