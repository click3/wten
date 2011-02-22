#include "stdafx.h"

namespace wten { namespace scenes {

namespace {

enum NEXT {
	NEXT_NEW_GAME,
	NEXT_LOAD_GAME,
	NEXT_EXIT,
};

} // anonymous

TitleScene::TitleScene() :
	exit(false), script_window(new windows::ScriptWindow())
{
	boost::optional<boost::shared_ptr<Error> > error = script_window->AddEventProc(EVENT_TYPE_ON_SELECT, boost::bind(&TitleScene::OnSelect, this, _1));
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

TitleScene::~TitleScene() {
}

boost::optional<boost::shared_ptr<Error> > TitleScene::SceneInitialize(void) {
	next_scene.reset();
	OPT_ERROR(AddWindow(script_window, 0, 0, 0, 0));

	boost::shared_ptr<const std::string> image_filename(new std::string("data/scene/title.png"));
	OPT_ERROR(AddImageUI(image_filename, uis::UIBase::MOVE_MODE_CENTER_FREE, 0, 50));

	std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > ui_list;
	const char *text_list[] = {
		"NewGame",
		"LoadGame",
		"Exit"
	};
	boost::shared_ptr<void> next_list[] = {
		boost::shared_ptr<void>(new NEXT(NEXT_NEW_GAME)),
		boost::shared_ptr<void>(new NEXT(NEXT_LOAD_GAME)),
		boost::shared_ptr<void>(new NEXT(NEXT_EXIT))
	};
	for(unsigned int i = 0; i < 3; i++) {
		boost::shared_ptr<const std::string> text(new std::string(text_list[i]));
		boost::shared_ptr<void> next(next_list[i]);
		ui_list.push_back(make_tuple(text, next));
	}
	OPT_ERROR(AddSelectorWindow(ui_list, 250, 300, 140, 80));
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > TitleScene::EnterFrame(void) {
	if(next_scene) {
		return next_scene;
	}
	if(exit) {
		return boost::shared_ptr<SceneExit>(new SceneExit());
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TitleScene::OnSelect(boost::shared_ptr<Event> event) {
	if(!event) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(event->GetEventType() != EVENT_TYPE_ON_SELECT) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	boost::shared_ptr<events::OnSelectEvent> on_select_event = boost::static_pointer_cast<events::OnSelectEvent>(event);
	boost::shared_ptr<void> user_data = on_select_event->GetUserData();
	if(!user_data) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	boost::shared_ptr<NEXT> next = boost::static_pointer_cast<NEXT>(user_data);
	switch(*next) {
		case NEXT_LOAD_GAME:
			OPT_ERROR(SaveDataLoad());
		case NEXT_NEW_GAME:
			next_scene.reset(new TownScene());
			break;
		case NEXT_EXIT:
			exit = true;
			break;
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > TitleScene::SaveDataLoad(void) {
	// TODO
	return boost::none;
}

} // scenes

} // wten

