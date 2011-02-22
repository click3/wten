#include "stdafx.h"

namespace wten { namespace scenes {

namespace {

enum STEP {
	GUILD_CREATE_DESCRIPTION_STEP,
	GUILD_NAME_INPUT_STEP,
	GUILD_CREATE_STEP,
	GUILD_CREATE_END_STEP,
	NORMAL_STEP,
};

boost::shared_ptr<const std::string> GetCastleName(void) {
	// TODO
	return boost::shared_ptr<const std::string>(new std::string("�W�[�N�t�����g�R�m�c����"));
}

unsigned int GetCurrentStep(void) {
	// TODO
	return 0;
}

} // anonymous


CastleScene::CastleScene() :
	step(GetCurrentStep()), title(GetCastleName()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(script_window);

	boost::optional<boost::shared_ptr<Error> > error = AddEvent(EVENT_TYPE_NEXT_STEP);
	if(error) {
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
	switch(step) {
		case GUILD_CREATE_DESCRIPTION_STEP: {
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
			const char *text_char = 
				"�܂��ł��Ă��܂���";
			boost::shared_ptr<const std::string> text(new std::string(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case GUILD_CREATE_STEP: {
			const char *text_char = 
				"�ނɏ����I�������ނ�n���ƁA�����Ɩڂ�ʂ�����\n"
				"���G�Ȉӏ����{���ꂽ���_���̂悤�ȕ���n���ꂽ�B\n"
				"\n"
				"�ǂ���疳���M���h�̌������I�����悤���B\n"
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
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CastleScene::OnEvent(boost::shared_ptr<Event> event) {
	if(event->GetEventType() == EVENT_TYPE_NEXT_STEP) {
		step++;
		return StepInitialize();
	}
	switch(step) {
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

