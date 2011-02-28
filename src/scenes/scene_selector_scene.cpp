#include "stdafx.h"
#include <iterator>
#include <functional>

namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

namespace {

std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > CreateSelectList(const std::vector<SceneSelectorScene::SCENE_PAIR>& scene_list) {
	std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > result;
	BOOST_FOREACH(SceneSelectorScene::SCENE_PAIR scene_pair, scene_list) {
		boost::shared_ptr<const std::string> text;
		boost::shared_ptr<void> scene;
		boost::tie(text, scene) = scene_pair;
		result += boost::make_tuple(text, scene);
	}
	return result;
}

} // anonymous

SceneSelectorScene::SceneSelectorScene(boost::shared_ptr<const std::string> title, const std::vector<SCENE_PAIR>& scene_list) :
	title(title), scene_list(scene_list), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(scene_list.size() > 0);
	BOOST_ASSERT(script_window);
	BOOST_FOREACH(SCENE_PAIR scene_pair, scene_list) {
		boost::shared_ptr<const std::string> text;
		boost::shared_ptr<Scene> scene;
		boost::tie(text, scene) = scene_pair;
		BOOST_ASSERT(text);
		BOOST_ASSERT(!text->empty());
		BOOST_ASSERT(scene);
	}

	boost::optional<boost::shared_ptr<Error> > error = script_window->AddEventProc(EVENT_TYPE_ON_SELECT, boost::bind(&SceneSelectorScene::OnSelect, this, _1));
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

SceneSelectorScene::~SceneSelectorScene() {
}

boost::optional<boost::shared_ptr<Error> > SceneSelectorScene::SceneInitialize(void) {
	OPT_ERROR(CampScene::SceneInitialize());
	next_scene.reset();
	OPT_ERROR(AddWindow(script_window, 0, 0, 0, 0));
	OPT_ERROR(AddBoxUI(uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(title, uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	OPT_ERROR(AddSelectorWindow(CreateSelectList(scene_list), 1, 50, 100, 540, 150));
	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > SceneSelectorScene::OnSelect(boost::shared_ptr<Event> event) {
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
	next_scene = boost::static_pointer_cast<Scene>(user_data);
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > SceneSelectorScene::EnterFrame(void) {
	if(next_scene) {
		return next_scene;
	}
	return boost::none;
}

} // scenes

} // wten

