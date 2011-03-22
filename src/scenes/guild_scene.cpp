#include "stdafx.h"

namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

namespace {

enum STEP {
	NORMAL_STEP,
	NEW_CHARACTER_STEP,
	CHARACTER_MANAGE_STEP,
	PT_SETTING_STEP,
	STAY_STEP,
	CONTRIBUTION_STEP,
	RETURN_STEP,
};

boost::shared_ptr<std::wstring> GetTitle(void) {
	// TODO
	return boost::shared_ptr<std::wstring>(new std::wstring(L"ñ`åØé“ÉMÉãÉh"));
}

unsigned int GetCurrentStep(void) {
	return GlobalData::GetCurrentInstance()->GetCurrentGuildStep();
}

void SetCurrentStep(STEP step) {
	GlobalData::GetCurrentInstance()->SetCurrentGuildStep(step);
}

void SendNextStepEvent(void) {
	boost::shared_ptr<Event> event(new events::NextStepEvent());
	EventNotify::Send(event);
}

} // anonymous

void GuildScene::Initialize(void) {
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

GuildScene::GuildScene(boost::shared_ptr<const std::wstring> default_frame_filename) :
	CampScene(default_frame_filename), current_step(GetCurrentStep()), title(GetTitle()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(!title->empty());
	BOOST_ASSERT(script_window);
	BOOST_ASSERT(!next_scene);
	Initialize();
}

GuildScene::GuildScene(boost::shared_ptr<const Graph> default_frame_graph) :
	CampScene(default_frame_graph), current_step(GetCurrentStep()), title(GetTitle()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(!title->empty());
	BOOST_ASSERT(script_window);
	BOOST_ASSERT(!next_scene);
	Initialize();
}

GuildScene::~GuildScene() {
}

boost::optional<boost::shared_ptr<Error> > GuildScene::SceneInitialize(void) {
	OPT_ERROR(CampScene::SceneInitialize());
	next_scene.reset();
	OPT_ERROR(AddWindow(script_window, 0, 0, 0, 0));
	OPT_ERROR(AddBoxUI(uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(title, uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));
	return StepInitialize();
}

boost::optional<boost::shared_ptr<Error> > GuildScene::StepInitialize(void) {
	switch(current_step) {
		case NORMAL_STEP: {
			std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > ui_list;
			const wchar_t *text_list[] = {
				L"êVÇΩÇ…ñ`åØé“Çìoò^Ç∑ÇÈ",
				L"ñ`åØé“Çä«óùÇ∑ÇÈ",
				L"PTÇï“ê¨Ç∑ÇÈ",
				L"èhîëÇ∑ÇÈ",
				L"äÒïtÇ∑ÇÈ",
				L"äOÇ…èoÇÈ"
			};
			boost::shared_ptr<void> step_list[] = {
				boost::shared_ptr<void>(new STEP(NEW_CHARACTER_STEP)),
				boost::shared_ptr<void>(new STEP(CHARACTER_MANAGE_STEP)),
				boost::shared_ptr<void>(new STEP(PT_SETTING_STEP)),
				boost::shared_ptr<void>(new STEP(STAY_STEP)),
				boost::shared_ptr<void>(new STEP(CONTRIBUTION_STEP)),
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
		case NEW_CHARACTER_STEP:
			// TODO
		case CHARACTER_MANAGE_STEP:
			// TODO
		case PT_SETTING_STEP:
			// TODO
		case STAY_STEP:
			// TODO
		case CONTRIBUTION_STEP:
			// TODO
		{
			next_step = NORMAL_STEP;
			const wchar_t *text_char = L"åªç›ñ¢é¿ëïÇ≈Ç∑ÅB";
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

boost::optional<boost::shared_ptr<Error> > GuildScene::OnEvent(boost::shared_ptr<Event> event) {
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

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > GuildScene::EnterFrame(void) {
	if(next_scene) {
		return next_scene;
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > GuildScene::AddEvent(EVENT_TYPE event_type) {
	BOOST_ASSERT(script_window);
	return script_window->AddEventProc(event_type, boost::bind(&GuildScene::OnEvent, this, _1));
}

} // scenes

} // wten

