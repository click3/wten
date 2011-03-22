#include "stdafx.h"

namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

namespace {

enum STEP {
	NORMAL_STEP,
	STAY_SELECT_STEP,
	STAY_MEWS_STEP,
	STAY_SIMPLE_STEP,
	STAY_ECONOMY_STEP,
	STAY_SUITE_STEP,
	STAY_ROYAL_SUITE_STEP,
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
	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));
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
			const wchar_t *text_list[] = {
				L"馬小屋",
				L"簡易寝台",
				L"エコノミールーム",
				L"スイートルーム",
				L"ロイヤルスイート",
				L"やめる"
			};
			boost::shared_ptr<void> step_list[] = {
				boost::shared_ptr<void>(new STEP(STAY_MEWS_STEP)),
				boost::shared_ptr<void>(new STEP(STAY_SIMPLE_STEP)),
				boost::shared_ptr<void>(new STEP(STAY_ECONOMY_STEP)),
				boost::shared_ptr<void>(new STEP(STAY_SUITE_STEP)),
				boost::shared_ptr<void>(new STEP(STAY_ROYAL_SUITE_STEP)),
				boost::shared_ptr<void>(new STEP(NORMAL_STEP))
			};
			for(unsigned int i = 0; i < 6; i++) {
				boost::shared_ptr<const std::wstring> text(new std::wstring(text_list[i]));
				boost::shared_ptr<void> step(step_list[i]);
				ui_list.push_back(make_tuple(text, step));
			}
			OPT_ERROR(AddSelectorWindow(ui_list, 1, ui_list.size()-1, 50, 100, 540, 180));
			break;
		}
		case STAY_MEWS_STEP:
		case STAY_SIMPLE_STEP:
		case STAY_ECONOMY_STEP:
		case STAY_SUITE_STEP:
		case STAY_ROYAL_SUITE_STEP:
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

