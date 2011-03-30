#include "stdafx.h"

namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

namespace {

const wchar_t *stay_name_list[] = {
	L"馬小屋",
	L"簡易寝台",
	L"エコノミールーム",
	L"スイートルーム",
	L"ロイヤルスイート"
};

const unsigned int stay_money_list[] = {
	0,
	10,
	50,
	200,
	500
};

unsigned int GetStayPrice(unsigned int bed_lv, unsigned int pt_count) {
	return stay_money_list[bed_lv] * pt_count;
}

enum STEP {
	NORMAL_STEP,
	STAY_SELECT_STEP,
	STAY_MEWS_STEP,
	STAY_SIMPLE_STEP,
	STAY_ECONOMY_STEP,
	STAY_SUITE_STEP,
	STAY_ROYAL_SUITE_STEP,
	STAY_MONEY_CHECK_STEP,
	STAY_WANT_MONEY_STEP,
	STAY_STEP,
	STAY_LEVEL_UP_CHECK,
	STAY_LEVEL_UP_VIEW,
	ITEM_STORE_IN_LIST_STEP,
	ITEM_STORE_IN_STEP,
	ITEM_STORE_OUT_LIST_STEP,
	ITEM_STORE_OUT_CHARACTER_SELECT_STEP,
	ITEM_STORE_OUT_EMPTY_STEP,
	MONEY_STORE_IN_STEP,
	MONEY_STORE_OUT_STEP,
	RETURN_STEP,
};

boost::shared_ptr<std::wstring> GetTitle(void) {
	// TODO
	return boost::shared_ptr<std::wstring>(new std::wstring(L"宿屋「ローゼンメイデン」"));
}

unsigned int GetCurrentStep(void) {
	return GlobalData::GetCurrentInstance()->GetCurrentHotelStep();
}

void SetCurrentStep(STEP step) {
	GlobalData::GetCurrentInstance()->SetCurrentHotelStep(step);
}

void SendNextStepEvent(void) {
	boost::shared_ptr<Event> event(new events::NextStepEvent());
	EventNotify::Send(event);
}

} // anonymous

void HotelScene::Initialize(void) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = AddEvent(EVENT_TYPE_NEXT_STEP)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	if(error = AddEvent(EVENT_TYPE_ON_SELECT)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

HotelScene::HotelScene(boost::shared_ptr<const std::wstring> default_frame_filename) :
	CampScene(default_frame_filename), current_step(GetCurrentStep()), title(GetTitle()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(!title->empty());
	BOOST_ASSERT(script_window);
	BOOST_ASSERT(!next_scene);
	Initialize();
}

HotelScene::HotelScene(boost::shared_ptr<const Graph> default_frame_graph) :
	CampScene(default_frame_graph), current_step(GetCurrentStep()), title(GetTitle()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(!title->empty());
	BOOST_ASSERT(script_window);
	BOOST_ASSERT(!next_scene);
	Initialize();
}

HotelScene::~HotelScene() {
}

boost::optional<boost::shared_ptr<Error> > HotelScene::SceneInitialize(void) {
	OPT_ERROR(CampScene::SceneInitialize());
	next_scene.reset();
	OPT_ERROR(AddWindow(script_window, 0, 0, 0, 0));
	OPT_ERROR(AddBoxUI(uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(title, uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, DEFAULT_SCREEN_SIZE_X, 130));
	return StepInitialize();
}

boost::optional<boost::shared_ptr<Error> > HotelScene::StepInitialize(void) {
	switch(current_step) {
		case NORMAL_STEP: {
			std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > ui_list;
			const wchar_t *text_list[] = {
				L"宿泊する",
				L"アイテムを預ける",
				L"アイテムを引き出す",
				L"お金を預ける",
				L"お金を引き出す",
				L"外に出る"
			};
			boost::shared_ptr<void> step_list[] = {
				boost::shared_ptr<void>(new STEP(STAY_SELECT_STEP)),
				boost::shared_ptr<void>(new STEP(ITEM_STORE_IN_LIST_STEP)),
				boost::shared_ptr<void>(new STEP(ITEM_STORE_OUT_LIST_STEP)),
				boost::shared_ptr<void>(new STEP(MONEY_STORE_IN_STEP)),
				boost::shared_ptr<void>(new STEP(MONEY_STORE_OUT_STEP)),
				boost::shared_ptr<void>(new STEP(RETURN_STEP))
			};
			for(unsigned int i = 0; i < 6; i++) {
				boost::shared_ptr<const std::wstring> text(new std::wstring(text_list[i]));
				boost::shared_ptr<void> step(step_list[i]);
				ui_list.push_back(make_tuple(text, step));
			}
			OPT_ERROR(AddSelectorWindow(ui_list, 1, ui_list.size()-1, 50, 100, 540, 180));
			break;
		}
		case STAY_SELECT_STEP: {
			std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > ui_list;
			std::vector<const wchar_t*> text_list;
			BOOST_FOREACH(const wchar_t *stay_name, stay_name_list) {
				text_list += stay_name;
			};
			text_list += L"やめる";
			boost::shared_ptr<void> step_list[] = {
				boost::shared_ptr<void>(new STEP(STAY_MEWS_STEP)),
				boost::shared_ptr<void>(new STEP(STAY_SIMPLE_STEP)),
				boost::shared_ptr<void>(new STEP(STAY_ECONOMY_STEP)),
				boost::shared_ptr<void>(new STEP(STAY_SUITE_STEP)),
				boost::shared_ptr<void>(new STEP(STAY_ROYAL_SUITE_STEP)),
				boost::shared_ptr<void>(new STEP(NORMAL_STEP))
			};
			for(unsigned int i = 0; i < text_list.size(); i++) {
				boost::shared_ptr<const std::wstring> text(new std::wstring(text_list[i]));
				boost::shared_ptr<void> step(step_list[i]);
				ui_list.push_back(make_tuple(text, step));
			}
			OPT_ERROR(AddSelectorWindow(ui_list, 1, ui_list.size()-1, 50, 100, 540, 180));
			break;
		}
		case STAY_MEWS_STEP:
			OPT_ERROR(StayStepInitialize(0));
			break;
		case STAY_SIMPLE_STEP:
			OPT_ERROR(StayStepInitialize(1));
			break;
		case STAY_ECONOMY_STEP:
			OPT_ERROR(StayStepInitialize(2));
			break;
		case STAY_SUITE_STEP:
			OPT_ERROR(StayStepInitialize(3));
			break;
		case STAY_ROYAL_SUITE_STEP:
			OPT_ERROR(StayStepInitialize(4));
			break;
		case STAY_MONEY_CHECK_STEP: {
			const unsigned int price = GetStayPrice(this->bed_lv, pt->size());
			unsigned int total_money = 0;
			BOOST_FOREACH(boost::shared_ptr<CharData> character, pt->GetCharacters()) {
				total_money += character->GetStatus()->GetTG();
			}
			if(total_money >= price) {
				next_step = STAY_STEP;
			} else {
				next_step = STAY_WANT_MONEY_STEP;
			}
			SendNextStepEvent();
			break;
		}
		case STAY_WANT_MONEY_STEP: {
			next_step = NORMAL_STEP;
			const wchar_t *text_char = L"お金が足りません。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case STAY_STEP: {
			next_step = STAY_LEVEL_UP_CHECK;
			wchar_t text_char[256];
			WSPRINTF(text_char, L"君たちは%sでゆっくりと疲れを癒した", stay_name_list[bed_lv]);
			const unsigned int price = GetStayPrice(this->bed_lv, pt->size());
			opt_error<std::vector<boost::optional<boost::shared_ptr<std::wstring> > > >::type opt_level_up_list = pt->Hotel(bed_lv, price);
			if(opt_level_up_list.which() == 0) {
				return boost::get<boost::shared_ptr<Error> >(opt_level_up_list);
			}
			level_up_list = boost::get<std::vector<boost::optional<boost::shared_ptr<std::wstring> > > >(opt_level_up_list);
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case STAY_LEVEL_UP_CHECK: {
			next_step = NORMAL_STEP;
			while(!level_up_list.empty()) {
				if(level_up_list.back()) {
					next_step = STAY_LEVEL_UP_VIEW;
					break;
				}
				level_up_list.pop_back();
			}
			SendNextStepEvent();
			break;
		}
		case STAY_LEVEL_UP_VIEW: {
			next_step = STAY_LEVEL_UP_CHECK;
			OPT_ERROR(AddTextWindow(level_up_list.back().get()));
			level_up_list.pop_back();
			break;
		}
		case ITEM_STORE_IN_LIST_STEP:
		case ITEM_STORE_IN_STEP:
		case ITEM_STORE_OUT_LIST_STEP:
		case ITEM_STORE_OUT_CHARACTER_SELECT_STEP:
		case ITEM_STORE_OUT_EMPTY_STEP:
		case MONEY_STORE_IN_STEP:
		case MONEY_STORE_OUT_STEP:
			// TODO
		{
			next_step = NORMAL_STEP;
			const wchar_t *text_char = L"現在未実装です。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case RETURN_STEP: {
			next_scene.reset(new TownScene(default_frame_graph));
			break;
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > HotelScene::StayStepInitialize(unsigned int bed_lv) {
	next_step = STAY_MONEY_CHECK_STEP;
	this->bed_lv = bed_lv;
	SendNextStepEvent();
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > HotelScene::OnEvent(boost::shared_ptr<Event> event) {
	if(event->GetEventType() == EVENT_TYPE_NEXT_STEP) {
		current_step = next_step;
		return StepInitialize();
	}
	switch(current_step) {
		case NORMAL_STEP:
		case STAY_SELECT_STEP: {
			if(event->GetEventType() == EVENT_TYPE_ON_SELECT) {
				boost::shared_ptr<events::OnSelectEvent> on_select_event = boost::static_pointer_cast<events::OnSelectEvent>(event);
				next_step = *boost::static_pointer_cast<STEP>(on_select_event->GetUserData());
				SendNextStepEvent();
			}
			break;
		}
	}
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > HotelScene::EnterFrame(void) {
	if(next_scene) {
		return next_scene;
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > HotelScene::AddEvent(EVENT_TYPE event_type) {
	BOOST_ASSERT(script_window);
	return script_window->AddEventProc(event_type, boost::bind(&HotelScene::OnEvent, this, _1));
}

} // scenes

} // wten

