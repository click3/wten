#include "stdafx.h"

namespace wten {

WTen::WTen(boost::shared_ptr<Scene> start_scene) :
	lib(new DxLibWrapper(true)),
	scene(start_scene)
{
	BOOST_ASSERT(lib);
	boost::optional<boost::shared_ptr<Error> > error = lib->SetDrawScreen(DxLibWrapper::SCREEN_MODE_BACK);
	if(error) {
		error.get()->Abort();
	}
}

WTen::~WTen() {
	scene.reset();
	lib.reset();
}

boost::optional<boost::shared_ptr<Error> > WTen::DoStart() {
	bool initialize = true;
	while(scene) {
		if(initialize) {
			boost::optional<boost::shared_ptr<Error> > result = scene->DoStart();
			if(result) {
				return result;
			}
			initialize = false;
		}
		LoopResult result = DoMainLoop();
		if(result.which() == 2) { // SceneExit
			break;
		}
		if(result.which() == 0) { // Error
			return boost::get<boost::shared_ptr<Error> >(result);
		}
		boost::optional<boost::shared_ptr<Scene> > next_scene = boost::get<boost::optional<boost::shared_ptr<Scene> > >(result);
		if(next_scene) {
			scene = next_scene.get();
			initialize = true;
		}
	}
	scene.reset();
	return boost::none;
}

WTen::LoopResult WTen::DoMainLoop(void) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(!lib->ProcessMessage()) {
		return boost::shared_ptr<SceneExit>(new SceneExit());
	}
	if(error = lib->ClearDrawScreen()) {
		return error.get();
	}
	LoopResult result = scene->DoNextFrame();
	if(error = lib->ScreenFlip()) {
		return error.get();
	}
	return result;
}

} // wten

