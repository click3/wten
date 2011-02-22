#include "stdafx.h"
#include <iterator>
#include <functional>

namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

OpeningScene::OpeningScene() :
	script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(script_window);

	boost::optional<boost::shared_ptr<Error> > error = script_window->AddEventProc(EVENT_TYPE_NEXT_STEP, boost::bind(&OpeningScene::NextStep, this, _1));
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

OpeningScene::~OpeningScene() {
}

boost::optional<boost::shared_ptr<Error> > OpeningScene::SceneInitialize(void) {
	next_scene.reset();
	OPT_ERROR(AddWindow(script_window, 0, 0, 0, 0));
	boost::shared_ptr<windows::WindowBase> op(new windows::OpeningWindow());
	OPT_ERROR(AddWindow(op,0,0,640,480));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > OpeningScene::NextStep(boost::shared_ptr<Event> event) {
	if(!event) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(event->GetEventType() != EVENT_TYPE_NEXT_STEP) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	next_scene.reset(new scenes::TitleScene());
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > OpeningScene::EnterFrame(void) {
	if(next_scene) {
		return next_scene;
	}
	return boost::none;
}

} // scenes

} // wten

