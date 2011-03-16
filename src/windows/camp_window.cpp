#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;
using namespace boost::assign;

namespace {

struct PTMoneyTotal {
	unsigned int operator ()(const unsigned int value, const boost::shared_ptr<const CharData> character) const {
		return value + character->GetStatus()->GetTG();
	}
};

boost::shared_ptr<uis::UIString> CreateMoneyText(boost::shared_ptr<PTData> pt) {
	std::vector<boost::shared_ptr<CharData> > characters = pt->GetCharacters();
	const unsigned int money_total = std::accumulate(characters.begin(), characters.end(), static_cast<unsigned int>(0), PTMoneyTotal());
	char text_char[256];
	SPRINTF(text_char, "所持金合計: %15dTG", money_total);
	boost::shared_ptr<std::string> text(new std::string(text_char));
	boost::shared_ptr<uis::UIString> result(new uis::UIString(text));
	return result;
}

boost::shared_ptr<uis::UIString> CreatePlayTimeText(void) {
	char text_char[256];
	SPRINTF(text_char, "プレイ時間: %s", PlayTime::GetCurrentInstance()->GetCurrentPlayTimeString()->c_str());
	boost::shared_ptr<std::string> text(new std::string(text_char));
	return boost::shared_ptr<uis::UIString>(new uis::UIString(text));
}

void SendNextWindowEvent(boost::shared_ptr<Window> window) {
	boost::shared_ptr<Event> event(new events::NextWindowEvent(window));
	EventNotify::Send(event);
}

void SendPopWindowEvent(boost::shared_ptr<Window> window) {
	boost::shared_ptr<Event> event(new events::PopWindowEvent(window));
	EventNotify::Send(event);
}

std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > CreateSelectList(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::string> default_frame_filename) {
	const char *text_list[] = {
		"アイテム",
		"装備",
		"ステータス",
		"隊列変更",
		"設定"
	};
	boost::shared_ptr<void> window_list[] = {
		boost::shared_ptr<void>(new CampItemWindow(pt, default_frame_filename)),
		boost::shared_ptr<void>(new CampBaseWindow(pt, default_frame_filename)),
		boost::shared_ptr<void>(new CampStatusWindow(pt, default_frame_filename)),
		boost::shared_ptr<void>(new CampBaseWindow(pt, default_frame_filename)),
		boost::shared_ptr<void>(new CampBaseWindow(pt, default_frame_filename))
	};
	std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > result;
	for(unsigned int i = 0; i < 5; i++) {
		boost::shared_ptr<const std::string> text(new std::string(text_list[i]));
		boost::shared_ptr<void> user_data = window_list[i];
		result += boost::make_tuple(text, user_data);
	}
	return result;
}

} // anonymous

CampWindow::CampWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::string> default_frame_filename) :
	WindowBase(default_frame_filename), pt(pt), money_text(CreateMoneyText(pt)), play_time_text(CreatePlayTimeText())
{
	BOOST_ASSERT(pt);
	BOOST_ASSERT(money_text);
	BOOST_ASSERT(play_time_text);
	boost::optional<boost::shared_ptr<Error> > error = this->Resize(640, 480);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

CampWindow::~CampWindow() {
}

boost::optional<boost::shared_ptr<Error> > CampWindow::WindowInitialize(void) {
	OPT_ERROR(AddBoxUI(uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	boost::shared_ptr<std::string> title(new std::string("キャンプ"));
	OPT_ERROR(AddTextUI(title, uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));

	select_window.reset(new SelectWindow(CreateSelectList(pt, default_frame_filename), 1, default_frame_filename));
	select_window->Move(50, 100);
	select_window->Resize(540, 150);
	select_window->SetSelectClose(false);
	SendNextWindowEvent(select_window);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampWindow::OnForeground(void) {
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampWindow::Resize(unsigned int width, unsigned int height) {
	if(width != 640 || height != 480) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return boost::none;
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type CampWindow::NotifyEvent(boost::shared_ptr<Event> event)  {
	BOOST_ASSERT(event);
	switch(event->GetEventType()) {
		case EVENT_TYPE_ON_SELECT: {
			boost::shared_ptr<events::OnSelectEvent> on_select_event = boost::static_pointer_cast<events::OnSelectEvent>(event);
			boost::shared_ptr<Window> window = boost::static_pointer_cast<Window>(on_select_event->GetUserData());
			SendNextWindowEvent(window);
			return boost::none;
		}
		case EVENT_TYPE_POP_WINDOW:
		case EVENT_TYPE_NEXT_WINDOW:
			break;
		case EVENT_TYPE_KEY: {
			boost::shared_ptr<events::KeyEvent> key_event = boost::static_pointer_cast<events::KeyEvent>(event);
			if(key_event->GetAction() == events::KeyEvent::KEY_PRESS) {
				switch(key_event->GetKey()) {
					case events::KeyEvent::KEY_B:
						SendPopWindowEvent(select_window);
						OPT_ERROR(RemoveThisWindow());
						break;
					default:
						break;
				}
			}
			return boost::none;
		}
		default:
			// 別のWindowと併用するため、ここでイベントを握りつぶしておく
			return boost::none;
	}
	return event;
}

} // windows

} // wten
