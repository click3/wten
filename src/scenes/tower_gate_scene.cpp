#include "stdafx.h"

namespace wten { namespace scenes {

namespace {

enum STEP {
	FIRST_STEP,
	GUILD_OK_STEP,
	NONE_GUILE_STEP,
	NORMAL_PT_CHECK_STEP,
	NONE_PT_STEP,
	NORMAL_STEP,
	TOWER_STEP,
	RETURN_STEP,
};

boost::shared_ptr<const std::wstring> GetTowerGateName(void) {
	// TODO
	return boost::shared_ptr<const std::wstring>(new std::wstring(L"天龍の塔　付近"));
}

unsigned int GetCurrentStep(void) {
	return GlobalData::GetCurrentInstance()->GetCurrentTowerStep();
}

void SetTowerStep(STEP step) {
	GlobalData::GetCurrentInstance()->SetCurrentTowerStep(step);
}

void SendNextStepEvent(void) {
	boost::shared_ptr<Event> event(new events::NextStepEvent());
	EventNotify::Send(event);
}

bool IsGuildCreate() {
	return GlobalData::GetCurrentInstance()->GetGuildCreate();
}


} // anonymous

void TowerGateScene::Initialize(void) {
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

TowerGateScene::TowerGateScene(boost::shared_ptr<const std::wstring> default_frame_filename) :
	CampScene(default_frame_filename), current_step(GetCurrentStep()), title(GetTowerGateName()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(script_window);
	Initialize();
}

TowerGateScene::TowerGateScene(boost::shared_ptr<const Graph> default_frame_graph) :
	CampScene(default_frame_graph), current_step(GetCurrentStep()), title(GetTowerGateName()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(script_window);
	Initialize();
}

TowerGateScene::~TowerGateScene() {
}

boost::optional<boost::shared_ptr<Error> > TowerGateScene::SceneInitialize(void) {
	OPT_ERROR(CampScene::SceneInitialize());
	next_scene.reset();
	OPT_ERROR(AddWindow(script_window, 0, 0, 0, 0));
	OPT_ERROR(AddBoxUI(uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(title, uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));
	return StepInitialize();
}

boost::optional<boost::shared_ptr<Error> > TowerGateScene::StepInitialize(void) {
	switch(current_step) {
		case FIRST_STEP: {
			const wchar_t *text_char = 
				L"君達が天龍の塔を目指し歩を進めていると、\n"
				L"守衛を名乗る人物により制止を受けた。\n"
				L"どうやら冒険者の入場はここで管理しているようだ。\n";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			if(IsGuildCreate()) {
				next_step = GUILD_OK_STEP;
			} else {
				next_step = NONE_GUILE_STEP;
			}
			break;
		}
		case GUILD_OK_STEP: {
			SetTowerStep(NORMAL_PT_CHECK_STEP);
			next_step = NORMAL_PT_CHECK_STEP;
			const wchar_t *text_char = 
				L"ギルド登録証を見せ手欲しいといわれたので\n"
				L"君達はギルド結成時に得たメダルのような物を\n"
				L"守衛に手渡した。\n"
				L"\n"
				L"守衛は銀色の宝石を手にメダルを調べるそぶりを見せ\n"
				L"暫くの後、メダルと共に通行証を差し出した。\n"
				L"\n"
				L"無事塔へ入場が許可されたようだ。\n"
				L"\n"
				L"君達は意気揚々と塔の入り口へと向かった。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case NONE_GUILE_STEP: {
			next_step = RETURN_STEP;
			const wchar_t *text_char = 
				L"ギルド登録証を見せるよう言われるが、\n"
				L"君達はそのようなものを所持していない。\n"
				L"\n"
				L"なんでも”騎士団の兵舎”で登録された冒険者以外\n"
				L"天龍の塔への入場は禁止されており\n"
				L"ギルド登録証はその証なのだという。\n"
				L"\n"
				L"ここはひとまず引き返し、\n"
				L"ギルド登録証を手に入れるべきだろう。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case NORMAL_PT_CHECK_STEP: {
			if(pt->GetCharacters().size() == 0) {
				next_step = NONE_PT_STEP;
			} else {
				next_step = NORMAL_STEP;
			}
			SendNextStepEvent();
			break;
		}
		case NONE_PT_STEP: {
			next_step = RETURN_STEP;
			const wchar_t *text_char = 
				L"君達はモンスターから身を守る手段を持っていない。\n"
				L"今ダンジョンに入るのは危険だ。\n"
				L"\n"
				L"ひとまず町に引き返しPTを整えるべきだろう。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case NORMAL_STEP: {
			std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > ui_list;
			const wchar_t *text_list[] = {
				L"天龍の塔に入る",
				L"町に戻る"
			};
			boost::shared_ptr<void> step_list[] = {
				boost::shared_ptr<void>(new STEP(TOWER_STEP)),
				boost::shared_ptr<void>(new STEP(RETURN_STEP))
			};
			for(unsigned int i = 0; i < 2; i++) {
				boost::shared_ptr<const std::wstring> text(new std::wstring(text_list[i]));
				boost::shared_ptr<void> step(step_list[i]);
				ui_list.push_back(make_tuple(text, step));
			}
			OPT_ERROR(AddSelectorWindow(ui_list, 1, ui_list.size() - 1, 50, 100, 540, 180));
			break;
		}
		case TOWER_STEP: {
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

boost::optional<boost::shared_ptr<Error> > TowerGateScene::OnEvent(boost::shared_ptr<Event> event) {
	if(event->GetEventType() == EVENT_TYPE_NEXT_STEP) {
		current_step = next_step;
		return StepInitialize();
	}
	switch(current_step) {
		case NORMAL_STEP: {
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

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > TowerGateScene::EnterFrame(void) {
	if(next_scene) {
		return next_scene;
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TowerGateScene::AddEvent(EVENT_TYPE event_type) {
	BOOST_ASSERT(script_window);
	return script_window->AddEventProc(event_type, boost::bind(&TowerGateScene::OnEvent, this, _1));
}

} // scenes

} // wten

