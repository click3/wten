#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;
using namespace boost::assign;

namespace {

const unsigned int page_size = 8;

boost::shared_ptr<uis::UIPager> CreateUIPageSelector(const std::vector<boost::shared_ptr<CharData> > &char_list, bool is_full_member) {
	std::vector<boost::shared_ptr<uis::UIBase> > page_list;
	std::vector<boost::shared_ptr<CharData> >::const_iterator it = char_list.begin();
	while(it != char_list.end() || !is_full_member) {
		std::vector<boost::shared_ptr<const std::wstring> > text_list;
		for(unsigned int i = 0; i < page_size && it != char_list.end(); i++) {
			text_list += (*it)->GetStatus()->GetName();
			++it;
		}
		bool break_flag = false;
		if(!is_full_member && text_list.size() != page_size) {
			text_list += WChar2Ptr(L"Œˆ’è");
			break_flag = true;
		}
		boost::shared_ptr<uis::UISelector> page(new uis::UISelector(text_list));
		page_list += page;
		if(break_flag) {
			break;
		}
	}
	return boost::shared_ptr<uis::UIPager>(new uis::UIPager(page_list));
}

boost::shared_ptr<uis::UITairetsu> CreateUITairetsu(boost::shared_ptr<const Graph> default_frame_graph) {
	return boost::shared_ptr<uis::UITairetsu>(new uis::UITairetsu(default_frame_graph));
}

} // anonymous

TairetsuWindow::TairetsuWindow(std::vector<boost::shared_ptr<CharData> > char_list, bool is_full_member, boost::shared_ptr<const std::wstring> default_frame_filename) :
	WindowBase(default_frame_filename), char_list(char_list), is_full_member(is_full_member), select_char(true), selected_char(), frame(new uis::UIBox(default_frame_graph)), selector(CreateUIPageSelector(char_list, is_full_member)), tairetsu(CreateUITairetsu(default_frame_graph)), cancel_event(boost::none)
{
	BOOST_ASSERT(frame);
}

TairetsuWindow::TairetsuWindow(std::vector<boost::shared_ptr<CharData> > char_list, bool is_full_member, boost::shared_ptr<const Graph> default_frame_graph) :
	WindowBase(default_frame_graph), char_list(char_list), is_full_member(is_full_member), select_char(true), selected_char(), frame(new uis::UIBox(default_frame_graph)), selector(CreateUIPageSelector(char_list, is_full_member)), tairetsu(CreateUITairetsu(default_frame_graph)), cancel_event(boost::none)
{
	BOOST_ASSERT(frame);
}

TairetsuWindow::~TairetsuWindow() {
}

void TairetsuWindow::SetCancelEvent(boost::optional<boost::shared_ptr<Event> > cancel_event) {
	this->cancel_event = cancel_event;
}

boost::optional<boost::shared_ptr<Error> > TairetsuWindow::WindowInitialize(void) {
	OPT_ERROR(WindowBase::WindowInitialize());
	OPT_ERROR(ResetUI());
	OPT_ERROR(AddUI(frame));
	OPT_ERROR(AddUI(tairetsu));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TairetsuWindow::ResetUI(void) {
	selector = CreateUIPageSelector(char_list, is_full_member);
	BOOST_ASSERT(selector);
	BOOST_ASSERT(frame);
	OPT_ERROR(frame->SetInnerUI(selector));
	OPT_ERROR(frame->Resize());
	const unsigned int frame_width = frame->GetWidth();
	const unsigned int frame_height = frame->GetHeight();
	BOOST_ASSERT(tairetsu);
	OPT_ERROR(tairetsu->Resize());
	const unsigned int tairetsu_width = tairetsu->GetWidth();
	const unsigned int tairetsu_height = tairetsu->GetHeight();
	if(frame_width + tairetsu_width > width || std::max(frame_height, tairetsu_height) > height) {
		return boost::none;
	}
	
	const unsigned int blank_width = (width - frame_width - tairetsu_width) / 3;
	const unsigned int blank_height = (height - std::max(frame_height, tairetsu_height)) / 2;

	const unsigned int frame_x = blank_width;
	const unsigned int frame_y = blank_height;
	OPT_ERROR(frame->Move(frame_x, frame_y));

	const unsigned int tairetsu_x = blank_width + frame_width + blank_width;
	const unsigned int tairetsu_y = blank_height;
	OPT_ERROR(tairetsu->Move(tairetsu_x, tairetsu_y));
	tairetsu->SetArrowEnable(!select_char);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TairetsuWindow::Move(unsigned int x, unsigned int y) {
	OPT_ERROR(WindowBase::Move(x, y));
	OPT_ERROR(ResetUI());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TairetsuWindow::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(WindowBase::Resize(width, height));
	OPT_ERROR(ResetUI());
	return boost::none;
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type TairetsuWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event);
	if(event->GetEventType() == EVENT_TYPE_KEY) {
		boost::shared_ptr<events::KeyEvent> key = boost::static_pointer_cast<events::KeyEvent>(event);
		if(key->GetAction() == events::KeyEvent::KEY_PRESS) {
			if(select_char) {
				switch(key->GetKey()) {
					case events::KeyEvent::KEY_UP:
						OPT_ERROR(boost::static_pointer_cast<uis::UISelector>(selector->GetPage())->Select(uis::UISelector::MOVE_FOCUS_UP));
						return boost::none;
					case events::KeyEvent::KEY_DOWN:
						OPT_ERROR(boost::static_pointer_cast<uis::UISelector>(selector->GetPage())->Select(uis::UISelector::MOVE_FOCUS_DOWN));
						return boost::none;
					case events::KeyEvent::KEY_RIGHT: {
						const unsigned int index = boost::static_pointer_cast<uis::UISelector>(selector->GetPage())->GetIndex();
						OPT_ERROR(selector->Select(uis::UIPager::MOVE_TYPE_NEXT));
						const boost::shared_ptr<uis::UISelector> page = boost::static_pointer_cast<uis::UISelector>(selector->GetPage());
						if(page->GetCount() > index) {
							OPT_ERROR(page->Select(index));
						} else {
							OPT_ERROR(page->Select(page->GetCount() - 1));
						}
						return boost::none;
					}
					case events::KeyEvent::KEY_LEFT: {
						const unsigned int index = boost::static_pointer_cast<uis::UISelector>(selector->GetPage())->GetIndex();
						OPT_ERROR(selector->Select(uis::UIPager::MOVE_TYPE_PREV));
						const boost::shared_ptr<uis::UISelector> page = boost::static_pointer_cast<uis::UISelector>(selector->GetPage());
						if(page->GetCount() > index) {
							OPT_ERROR(page->Select(index));
						} else {
							OPT_ERROR(page->Select(page->GetCount() - 1));
						}
						return boost::none;
					}
					case events::KeyEvent::KEY_A:
						OPT_ERROR(OnCharSelect());
						return boost::none;
					case events::KeyEvent::KEY_B:
						OPT_ERROR(OnCancelEvent());
						return boost::none;
					default:
						break;
				}
			} else {
				switch(key->GetKey()) {
					case events::KeyEvent::KEY_UP:
						OPT_ERROR(tairetsu->Select(uis::UITairetsu::MOVE_FOCUS_UP));
						return boost::none;
					case events::KeyEvent::KEY_DOWN:
						OPT_ERROR(tairetsu->Select(uis::UITairetsu::MOVE_FOCUS_DOWN));
						return boost::none;
					case events::KeyEvent::KEY_A:
						OPT_ERROR(OnTairetsuSelect());
						return boost::none;
					case events::KeyEvent::KEY_B:
						OPT_ERROR(OnTairetsuCancel());
						return boost::none;
					default:
						break;
				}
			}
		}
	}
	return event;
}

boost::optional<boost::shared_ptr<Error> > TairetsuWindow::OnCharSelect(void) {
	const unsigned int index = selector->GetIndex() * page_size + boost::static_pointer_cast<uis::UISelector>(selector->GetPage())->GetIndex();
	if(index == char_list.size()) {
		OPT_ERROR(OnTairetsuSelectedEvent());
		return boost::none;
	}
	selected_char = char_list[index];
	select_char = false;
	tairetsu->SetArrowEnable(true);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TairetsuWindow::OnTairetsuSelect(void) {
	std::vector<boost::shared_ptr<CharData> >::iterator it = std::find(char_list.begin(), char_list.end(), selected_char);
	BOOST_ASSERT(it != char_list.end());
	char_list.erase(it);
	boost::shared_ptr<CharData> char_data = tairetsu->Get();
	if(char_data) {
		char_list.push_back(char_data);
	}
	OPT_ERROR(tairetsu->Set(selected_char));
	if(char_list.empty()) {
		OPT_ERROR(OnTairetsuSelectedEvent());
		return boost::none;
	}
	selected_char.reset();
	select_char = true;
	tairetsu->SetArrowEnable(false);
	OPT_ERROR(ResetUI());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TairetsuWindow::OnTairetsuCancel(void) {
	selected_char.reset();
	select_char = true;
	tairetsu->SetArrowEnable(false);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TairetsuWindow::OnTairetsuSelectedEvent(void) {
	OPT_ERROR(RemoveThisWindow());
	boost::shared_ptr<Event> event(new events::TairetsuSelectedEvent(tairetsu->GetCharDataList()));
	EventNotify::Send(event);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TairetsuWindow::OnCancelEvent(void) {
	OPT_ERROR(RemoveThisWindow());
	if(cancel_event) {
		EventNotify::Send(cancel_event.get());
	}
	return boost::none;
}

} // windows

} // wten
