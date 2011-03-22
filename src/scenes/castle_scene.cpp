#include "stdafx.h"

namespace wten { namespace scenes {

namespace {

enum STEP {
	GUILD_CREATE_DESCRIPTION_STEP,
	GUILD_NAME_INPUT_STEP,
	GUILD_CREATE_CHECK_STEP,
	GUILD_CREATE_FAILURE_STEP,
	GUILD_CREATE_SUCCESS_STEP,
	GUILD_CREATE_END_STEP,
	NORMAL_STEP,
	NEW_MISSON_STEP,
	MISSON_REPORT_STEP,
	JOB_CHANGE_STEP,
	CONTRIBUTION_STEP,
	MONSTER_LIST_STEP,
	ITEM_LIST_STEP,
	RETURN_STEP,
};

boost::shared_ptr<const std::wstring> GetCastleName(void) {
	// TODO
	return boost::shared_ptr<const std::wstring>(new std::wstring(L"ジークフロント騎士団兵舎"));
}

unsigned int GetCurrentStep(void) {
	return GlobalData::GetCurrentInstance()->GetCurrentCastleStep();
}

void SendNextStepEvent(void) {
	boost::shared_ptr<Event> event(new events::NextStepEvent());
	EventNotify::Send(event);
}

void SetGuildName(boost::shared_ptr<const std::wstring> guild_name) {
	GlobalData::GetCurrentInstance()->SetGuildName(guild_name);
}

void SetCurrentCastleStep(STEP step) {
	GlobalData::GetCurrentInstance()->SetCurrentCastleStep(step);
}

void GuildCreateSuccess(void) {
	return GlobalData::GetCurrentInstance()->SetGuildCreate(true);
}

} // anonymous

void CastleScene::Initialize(void) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = AddEvent(EVENT_TYPE_NEXT_STEP)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	if(error = AddEvent(EVENT_TYPE_INPUT_STRING)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	if(error = AddEvent(EVENT_TYPE_ON_SELECT)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

CastleScene::CastleScene(boost::shared_ptr<const std::wstring> default_frame_filename) :
	CampScene(default_frame_filename), current_step(GetCurrentStep()), title(GetCastleName()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(script_window);
	Initialize();
}

CastleScene::CastleScene(boost::shared_ptr<const Graph> default_frame_graph) :
	CampScene(default_frame_graph), current_step(GetCurrentStep()), title(GetCastleName()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(script_window);
	Initialize();
}

CastleScene::~CastleScene() {
}

boost::optional<boost::shared_ptr<Error> > CastleScene::SceneInitialize(void) {
	OPT_ERROR(CampScene::SceneInitialize());
	next_scene.reset();
	OPT_ERROR(AddWindow(script_window, 0, 0, 0, 0));
	OPT_ERROR(AddBoxUI(uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(title, uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));
	return StepInitialize();
}

boost::optional<boost::shared_ptr<Error> > CastleScene::StepInitialize(void) {
	switch(current_step) {
		case GUILD_CREATE_DESCRIPTION_STEP: {
			next_step = GUILD_NAME_INPUT_STEP;
			const wchar_t *text_char = 
				L"君達が城内へと足を踏み入れると、\n"
				L"貴族然とした人物に声をかけられた。\n"
				L"どうやら冒険者の対応を仕事としている者のようだ。\n"
				L"\n"
				L"彼の説明によると、\n"
				L"塔に入るには軍属である”ギルド”に加わる必要があるらしい。\n"
				L"だが難しくはなく、個人であってもギルド結成は可能なようだ。\n"
				L"もちろんそれは君達にも当てはまる。\n"
				L"\n"
				L"君達はしばらく考えた後、新しくギルドを結成する事にした。\n"
				L"そのギルドの名は……";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case GUILD_NAME_INPUT_STEP: {
			next_step = GUILD_CREATE_CHECK_STEP;
			const wchar_t *message_char = L"ギルド名を入力してください";
			boost::shared_ptr<const std::wstring> message(new std::wstring(message_char));
			OPT_ERROR(AddInputDlgWindow(message));
			break;
		}
		case GUILD_CREATE_CHECK_STEP: {
			if(temp_data) {
				boost::shared_ptr<const std::wstring> text = boost::static_pointer_cast<const std::wstring>(temp_data);
				if(!text->empty()) {
					SetGuildName(text);
					SetCurrentCastleStep(NORMAL_STEP);
					GuildCreateSuccess();
					next_step = GUILD_CREATE_SUCCESS_STEP;
				} else {
					next_step = GUILD_CREATE_FAILURE_STEP;
				}
			} else {
				next_step = GUILD_CREATE_FAILURE_STEP;
			}
			SendNextStepEvent();
			break;
		}
		case GUILD_CREATE_FAILURE_STEP: {
			next_step = GUILD_NAME_INPUT_STEP;
			const wchar_t *text_char = 
				L"彼に書き終えた書類を渡すと、さっと目を通した後\n"
				L"ギルド名の空欄を指摘された。\n"
				L"\n"
				L"どうやらギルド名は必須のようだ\n"
				L"\n"
				L"君達は再度書類に向かい、ギルド名を考えなおす事にする。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case GUILD_CREATE_SUCCESS_STEP: {
			next_step = GUILD_CREATE_END_STEP;
			const wchar_t *text_char = 
				L"彼に書き終えた書類を渡すと、さっと目を通した後\n"
				L"複雑な意匠が施されたメダルのような物を渡された。\n"
				L"\n"
				L"どうやら無事ギルドの結成を終えられたようだ。\n"
				L"これで塔に入る事も可能だろう。\n"
				L"\n"
				L"君達は彼に礼を言うとその場を後にした。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case GUILD_CREATE_END_STEP: {
			next_scene.reset(new TownScene(default_frame_graph));
			break;
		}
		case NORMAL_STEP: {
			std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > ui_list;
			const wchar_t *text_list[] = {
				L"ミッションを受ける",
				L"ミッションを報告する",
				L"転職する",
				L"寄付する",
				L"モンスター図鑑を見る",
				L"アイテム図鑑を見る",
				L"外に出る"
			};
			boost::shared_ptr<void> step_list[] = {
				boost::shared_ptr<void>(new STEP(NEW_MISSON_STEP)),
				boost::shared_ptr<void>(new STEP(MISSON_REPORT_STEP)),
				boost::shared_ptr<void>(new STEP(JOB_CHANGE_STEP)),
				boost::shared_ptr<void>(new STEP(CONTRIBUTION_STEP)),
				boost::shared_ptr<void>(new STEP(MONSTER_LIST_STEP)),
				boost::shared_ptr<void>(new STEP(ITEM_LIST_STEP)),
				boost::shared_ptr<void>(new STEP(RETURN_STEP))
			};
			for(unsigned int i = 0; i < 7; i++) {
				boost::shared_ptr<const std::wstring> text(new std::wstring(text_list[i]));
				boost::shared_ptr<void> step(step_list[i]);
				ui_list.push_back(make_tuple(text, step));
			}
			OPT_ERROR(AddSelectorWindow(ui_list, 1, ui_list.size()-1, 50, 100, 540, 180));
			break;
		}
		case NEW_MISSON_STEP:
			// TODO
		case MISSON_REPORT_STEP:
			// TODO
		case JOB_CHANGE_STEP:
			// TODO
		case CONTRIBUTION_STEP:
			// TODO
		case MONSTER_LIST_STEP:
			// TODO
		case ITEM_LIST_STEP:
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

boost::optional<boost::shared_ptr<Error> > CastleScene::OnEvent(boost::shared_ptr<Event> event) {
	if(event->GetEventType() == EVENT_TYPE_NEXT_STEP) {
		current_step = next_step;
		return StepInitialize();
	}
	switch(current_step) {
		case GUILD_NAME_INPUT_STEP: {
			if(event->GetEventType() == EVENT_TYPE_INPUT_STRING) {
				boost::shared_ptr<events::InputStringEvent> input_string_event = boost::static_pointer_cast<events::InputStringEvent>(event);
				temp_data = input_string_event->GetText();
				SendNextStepEvent();
			}
			break;
		}
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

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > CastleScene::EnterFrame(void) {
	if(next_scene) {
		return next_scene;
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CastleScene::AddEvent(EVENT_TYPE event_type) {
	BOOST_ASSERT(script_window);
	return script_window->AddEventProc(event_type, boost::bind(&CastleScene::OnEvent, this, _1));
}

} // scenes

} // wten

