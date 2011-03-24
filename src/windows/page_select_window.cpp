#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;
using namespace boost::assign;

namespace {

typedef boost::tuple<boost::shared_ptr<uis::UIBase>, boost::shared_ptr<void> > UI_PAIR;

std::vector<boost::shared_ptr<uis::UISelectorBase> > CreateSelectorList(const std::vector<UI_PAIR>& input, unsigned int page_size) {
	std::vector<boost::shared_ptr<uis::UISelectorBase> > result;
	const unsigned int page_count = static_cast<unsigned int>(::ceil((double)input.size() / page_size));
	std::vector<UI_PAIR>::const_iterator it = input.begin();
	for(unsigned int i = 0; i < page_count; i++) {
		std::vector<boost::shared_ptr<uis::UIBase> > select_list;
		std::vector<UI_PAIR>::const_iterator end;
		if(static_cast<unsigned int>(std::distance(it, input.end())) <= page_size) {
			end = input.end();
		} else {
			end = it;
			std::advance(end, page_size);
		}
		for(; it != end; ++it) {
			select_list.push_back(boost::static_pointer_cast<uis::UIBase>(it->get<0>()));
		}
		const boost::shared_ptr<uis::UISelectorBase> selector(new uis::UISelectorBase(select_list));
		result.push_back(selector);
	}
	return result;
}

std::vector<std::vector<boost::shared_ptr<void> > > CreateDataList(const std::vector<UI_PAIR>& input, unsigned int page_size) {
	std::vector<std::vector<boost::shared_ptr<void> > > result;
	const unsigned int page_count = static_cast<unsigned int>(::ceil((double)input.size() / page_size));
	std::vector<UI_PAIR>::const_iterator it = input.begin();
	for(unsigned int i = 0; i < page_count; i++) {
		std::vector<boost::shared_ptr<void> > row;
		std::vector<UI_PAIR>::const_iterator end;
		if(static_cast<unsigned int>(std::distance(it, input.end())) <= page_size) {
			end = input.end();
		} else {
			end = it;
			std::advance(end, page_size);
		}
		for(; it != end; ++it) {
			row.push_back(it->get<1>());
		}
		result.push_back(row);
	}
	return result;
}

boost::shared_ptr<uis::UIPager> CreateUIPager(const std::vector<boost::shared_ptr<uis::UISelectorBase> > &selector_list) {
	std::vector<boost::shared_ptr<uis::UIBase> > ui_list;
	boost::copy(selector_list, std::back_inserter(ui_list));
	boost::shared_ptr<uis::UIPager> result(new uis::UIPager(ui_list));
	return result;
}

} // anonymous

PageSelectWindow::PageSelectWindow(const std::vector<UI_PAIR>& input, unsigned int page_size, boost::shared_ptr<const std::wstring> frame_filename) :
	WindowBase(frame_filename), select_close(true), selector_list(CreateSelectorList(input, page_size)), pager(CreateUIPager(selector_list)), frame(new uis::UIBox(default_frame_graph)), data_list(CreateDataList(input, page_size)), cancel_data()
{
	BOOST_ASSERT(selector_list.size() == data_list.size());
	BOOST_ASSERT(frame);
	unsigned int i = 0;
	BOOST_FOREACH(boost::shared_ptr<uis::UISelectorBase> selector, selector_list) {
		BOOST_ASSERT(selector);
		BOOST_FOREACH(boost::shared_ptr<void> data, data_list[i]) {
			BOOST_ASSERT(data);
		}
		i++;
	}
}

PageSelectWindow::PageSelectWindow(const std::vector<boost::tuple<boost::shared_ptr<uis::UIBase>, boost::shared_ptr<void> > >& input, unsigned int page_size, boost::shared_ptr<const Graph> frame) :
	WindowBase(frame), select_close(true), selector_list(CreateSelectorList(input, page_size)), pager(CreateUIPager(selector_list)), frame(new uis::UIBox(default_frame_graph)), data_list(CreateDataList(input, page_size)), cancel_data()
{
	BOOST_ASSERT(selector_list.size() == data_list.size());
	BOOST_ASSERT(frame);
	unsigned int i = 0;
	BOOST_FOREACH(boost::shared_ptr<uis::UISelectorBase> selector, selector_list) {
		BOOST_ASSERT(selector);
		BOOST_ASSERT(data_list[i].size() <= page_size);
		BOOST_FOREACH(boost::shared_ptr<void> data, data_list[i]) {
			BOOST_ASSERT(data);
		}
		i++;
	}
}

PageSelectWindow::~PageSelectWindow() {
}

bool PageSelectWindow::IsSelectClose(void) const {
	return select_close;
}

void PageSelectWindow::SetSelectClose(bool flag) {
	select_close = flag;
}

boost::optional<boost::shared_ptr<Error> > PageSelectWindow::SetCancelData(boost::optional<boost::shared_ptr<void> > data) {
	cancel_data = data;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > PageSelectWindow::WindowInitialize(void) {
	OPT_ERROR(WindowBase::WindowInitialize());
	OPT_ERROR(AddUI(frame));
	OPT_ERROR(AddUI(pager));
	unsigned int pager_x;
	OPT_UINT(pager_x, frame->CalcWidth());
	pager_x /= 2;
	unsigned int pager_y;
	OPT_UINT(pager_y, frame->CalcHeight());
	pager_y /= 2;
	OPT_ERROR(pager->Move(pager_x, pager_y));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > PageSelectWindow::Resize() {
	unsigned int width, height;
	OPT_ERROR(pager->Resize());
	OPT_PAIR_UINT(width, height, pager->GetSize());
	unsigned int frame_w, frame_h;
	OPT_ERROR(frame->Resize());
	OPT_PAIR_UINT(frame_w, frame_h, frame->GetSize());
	width += frame_w;
	height += frame_h;
	return Resize(width, height);
}

boost::optional<boost::shared_ptr<Error> > PageSelectWindow::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(WindowBase::Resize(width, height));
	OPT_ERROR(frame->Resize(width, height));
	unsigned int frame_width;
	OPT_UINT(frame_width, frame->CalcWidth());
	unsigned int frame_height;
	OPT_UINT(frame_height, frame->CalcHeight());
	OPT_ERROR(pager->Resize(width - frame_width, height - frame_height));
	return boost::none;
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type PageSelectWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event);
	if(event->GetEventType() == EVENT_TYPE_KEY) {
		boost::shared_ptr<events::KeyEvent> key = boost::static_pointer_cast<events::KeyEvent>(event);
		if(key->GetAction() == events::KeyEvent::KEY_PRESS) {
			BOOST_ASSERT(selector_list.size() > pager->GetIndex());
			switch(key->GetKey()) {
				case events::KeyEvent::KEY_UP:
					OPT_ERROR(selector_list[pager->GetIndex()]->Select(uis::UISelectorBase::MOVE_FOCUS_UP));
					OPT_ERROR(OnSelectChange());
					return boost::none;
				case events::KeyEvent::KEY_DOWN:
					OPT_ERROR(selector_list[pager->GetIndex()]->Select(uis::UISelectorBase::MOVE_FOCUS_DOWN));
					OPT_ERROR(OnSelectChange());
					return boost::none;
				case events::KeyEvent::KEY_RIGHT: {
					const unsigned int index = selector_list[pager->GetIndex()]->GetIndex();
					OPT_ERROR(pager->Select(uis::UIPager::MOVE_TYPE_NEXT));
					if(selector_list[pager->GetIndex()]->GetCount() > index) {
						OPT_ERROR(selector_list[pager->GetIndex()]->Select(index));
					} else {
						OPT_ERROR(selector_list[pager->GetIndex()]->Select(selector_list[pager->GetIndex()]->GetCount() - 1));
					}
					OPT_ERROR(OnSelectChange());
					return boost::none;
				}
				case events::KeyEvent::KEY_LEFT: {
					const unsigned int index = selector_list[pager->GetIndex()]->GetIndex();
					OPT_ERROR(pager->Select(uis::UIPager::MOVE_TYPE_PREV));
					if(selector_list[pager->GetIndex()]->GetCount() > index) {
						OPT_ERROR(selector_list[pager->GetIndex()]->Select(index));
					} else {
						OPT_ERROR(selector_list[pager->GetIndex()]->Select(selector_list[pager->GetIndex()]->GetCount() - 1));
					}
					OPT_ERROR(OnSelectChange());
					return boost::none;
				}
				case events::KeyEvent::KEY_A:
					OPT_ERROR(OnSelect());
					return boost::none;
				case events::KeyEvent::KEY_B:
					if(cancel_data) {
						OPT_ERROR(OnCancel());
						return boost::none;
					}
					// cancel_datañ¢ê›íËÇÃèÍçáÇÕå„ë±ÇÃwindowÇ…ÉCÉxÉìÉgÇó¨Ç∑
					break;
				default:
					break;
			}
		}
	}
	return event;
}

boost::optional<boost::shared_ptr<Error> > PageSelectWindow::OnSelect(void) {
	const unsigned int page_index = pager->GetIndex();
	BOOST_ASSERT(page_index < data_list.size());
	unsigned int selector_index;
	OPT_UINT(selector_index, selector_list[pager->GetIndex()]->GetIndex());
	BOOST_ASSERT(selector_index < data_list[page_index].size());
	const boost::shared_ptr<void> data = data_list[page_index][selector_index];
	boost::shared_ptr<Event> event(new events::OnSelectEvent(data));
	if(select_close) {
		OPT_ERROR(RemoveThisWindow());
	}
	EventNotify::Send(event);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > PageSelectWindow::OnSelectChange(void) {
	const unsigned int page_index = pager->GetIndex();
	BOOST_ASSERT(page_index < data_list.size());
	unsigned int selector_index;
	OPT_UINT(selector_index, selector_list[pager->GetIndex()]->GetIndex());
	BOOST_ASSERT(selector_index < data_list[page_index].size());
	const boost::shared_ptr<void> data = data_list[page_index][selector_index];
	boost::shared_ptr<Event> event(new events::OnSelectChangeEvent(data));
	EventNotify::Send(event);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > PageSelectWindow::OnCancel(void) {
	if(!cancel_data) {
		return boost::none;
	}
	boost::shared_ptr<Event> event(new events::OnSelectEvent(cancel_data.get()));
	if(select_close) {
		OPT_ERROR(RemoveThisWindow());
	}
	EventNotify::Send(event);
	return boost::none;
}

} // windows

} // wten
