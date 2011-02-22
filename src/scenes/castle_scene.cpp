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

boost::shared_ptr<const std::string> GetCastleName(void) {
	// TODO
	return boost::shared_ptr<const std::string>(new std::string("�W�[�N�t�����g�R�m�c����"));
}

unsigned int GetCurrentStep(void) {
	return GlobalData::GetCurrentInstance()->GetCurrentCastleStep();
}

void SendNextStepEvent(void) {
	boost::shared_ptr<Event> event(new events::NextStepEvent());
	EventNotify::Send(event);
}

void SetGuildName(boost::shared_ptr<const std::string> guild_name) {
	GlobalData::GetCurrentInstance()->SetGuildName(guild_name);
}

void SetCurrentCastleStep(STEP step) {
	GlobalData::GetCurrentInstance()->SetCurrentCastleStep(step);
}

void GuildCreateSuccess(void) {
	return GlobalData::GetCurrentInstance()->SetGuildCreate(true);
}

} // anonymous


CastleScene::CastleScene() :
	current_step(GetCurrentStep()), title(GetCastleName()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(script_window);

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

CastleScene::~CastleScene() {
}

boost::optional<boost::shared_ptr<Error> > CastleScene::SceneInitialize(void) {
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
			const char *text_char = 
				"�N�B������ւƑ��𓥂ݓ����ƁA\n"
				"�M���R�Ƃ����l���ɐ���������ꂽ�B\n"
				"�ǂ����`���҂̑Ή����d���Ƃ��Ă���҂̂悤���B\n"
				"\n"
				"�ނ̐����ɂ��ƁA\n"
				"���ɓ���ɂ͌R���ł���h�M���h�h�ɉ����K�v������炵���B\n"
				"��������͂Ȃ��A�l�ł����Ă��M���h�����͉\�Ȃ悤���B\n"
				"������񂻂�͌N�B�ɂ����Ă͂܂�B\n"
				"\n"
				"�N�B�͂��΂炭�l������A�V�����M���h���������鎖�ɂ����B\n"
				"���̃M���h�̖��́c�c";
			boost::shared_ptr<const std::string> text(new std::string(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case GUILD_NAME_INPUT_STEP: {
			next_step = GUILD_CREATE_CHECK_STEP;
			const char *message_char = "�M���h������͂��Ă�������";
			boost::shared_ptr<const std::string> message(new std::string(message_char));
			OPT_ERROR(AddInputDlgWindow(message));
			break;
		}
		case GUILD_CREATE_CHECK_STEP: {
			if(temp_data) {
				boost::shared_ptr<const std::string> text = boost::static_pointer_cast<const std::string>(temp_data);
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
			const char *text_char = 
				"�ނɏ����I�������ނ�n���ƁA�����Ɩڂ�ʂ�����\n"
				"�M���h���̋󗓂��w�E���ꂽ�B\n"
				"\n"
				"�ǂ����M���h���͕K�{�̂悤��\n"
				"\n"
				"�N�B�͍ēx���ނɌ������A�M���h�����l���Ȃ������ɂ���B";
			boost::shared_ptr<const std::string> text(new std::string(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case GUILD_CREATE_SUCCESS_STEP: {
			next_step = GUILD_CREATE_END_STEP;
			const char *text_char = 
				"�ނɏ����I�������ނ�n���ƁA�����Ɩڂ�ʂ�����\n"
				"���G�Ȉӏ����{���ꂽ���_���̂悤�ȕ���n���ꂽ�B\n"
				"\n"
				"�ǂ���疳���M���h�̌������I����ꂽ�悤���B\n"
				"����œ��ɓ��鎖���\���낤�B\n"
				"\n"
				"�N�B�͔ނɗ�������Ƃ��̏����ɂ����B";
			boost::shared_ptr<const std::string> text(new std::string(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case GUILD_CREATE_END_STEP: {
			next_scene.reset(new TownScene());
			break;
		}
		case NORMAL_STEP: {
			std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > ui_list;
			const char *text_list[] = {
				"�~�b�V�������󂯂�",
				"�~�b�V������񍐂���",
				"�]�E����",
				"��t����",
				"�����X�^�[�}�ӂ�����",
				"�A�C�e���}�ӂ�����",
				"�O�ɏo��"
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
				boost::shared_ptr<const std::string> text(new std::string(text_list[i]));
				boost::shared_ptr<void> step(step_list[i]);
				ui_list.push_back(make_tuple(text, step));
			}
			OPT_ERROR(AddSelectorWindow(ui_list, 50, 100, 540, 180));
			break;
		}
		case NEW_MISSON_STEP:
		case MISSON_REPORT_STEP:
		case JOB_CHANGE_STEP:
		case CONTRIBUTION_STEP:
		case MONSTER_LIST_STEP:
		case ITEM_LIST_STEP: {
			next_step = NORMAL_STEP;
			const char *text_char = "���ݖ������ł��B";
			boost::shared_ptr<const std::string> text(new std::string(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case RETURN_STEP: {
			next_scene.reset(new TownScene());
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

boost::optional<boost::shared_ptr<Error> > CastleScene::AddTextWindow(boost::shared_ptr<const std::string> text) {
	return SceneBase::AddTextWindow(text, 50, 50, 540, 380);
}

} // scenes

} // wten

