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
};

boost::shared_ptr<const std::string> GetCastleName(void) {
	// TODO
	return boost::shared_ptr<const std::string>(new std::string("ジークフロント騎士団兵舎"));
}

unsigned int GetCurrentStep(void) {
	// TODO
	return 0;
}

void SendNextStepEvent(void) {
	boost::shared_ptr<Event> event(new events::NextStepEvent());
	EventNotify::Send(event);
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
				"君達が城内へと足を踏み入れると、\n"
				"貴族然とした人物に声をかけられた。\n"
				"どうやら冒険者の対応を仕事としている者のようだ。\n"
				"\n"
				"彼の説明によると、\n"
				"塔に入るには軍属である”ギルド”に加わる必要があるらしい。\n"
				"だが難しくはなく、個人であってもギルド結成は可能なようだ。\n"
				"もちろんそれは君達にも当てはまる。\n"
				"\n"
				"君達はしばらく考えた後、新しくギルドを結成する事にした。\n"
				"そのギルドの名は……";
			boost::shared_ptr<const std::string> text(new std::string(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case GUILD_NAME_INPUT_STEP: {
			next_step = GUILD_CREATE_CHECK_STEP;
			const char *message_char = "ギルド名を入力してください";
			boost::shared_ptr<const std::string> message(new std::string(message_char));
			OPT_ERROR(AddInputDlgWindow(message));
			break;
		}
		case GUILD_CREATE_CHECK_STEP: {
			if(temp_data) {
				boost::shared_ptr<const std::string> text = boost::static_pointer_cast<const std::string>(temp_data);
				if(!text->empty()) {
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
				"彼に書き終えた書類を渡すと、さっと目を通した後\n"
				"ギルド名の空欄を指摘された。\n"
				"\n"
				"どうやらギルド名は必須のようだ\n"
				"\n"
				"君達は再度書類に向かい、ギルド名を考えなおす事にする。";
			boost::shared_ptr<const std::string> text(new std::string(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case GUILD_CREATE_SUCCESS_STEP: {
			next_step = GUILD_CREATE_END_STEP;
			const char *text_char = 
				"彼に書き終えた書類を渡すと、さっと目を通した後\n"
				"複雑な意匠が施されたメダルのような物を渡された。\n"
				"\n"
				"どうやら無事ギルドの結成を終えられたようだ。\n"
				"これで塔に入る事も可能だろう。\n"
				"\n"
				"君達は彼に礼を言うとその場を後にした。";
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

