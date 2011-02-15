#include "stdafx.h"
#include "version.h"

namespace wten {

WTen::WTen(boost::shared_ptr<Scene> start_scene) :
	lib(new DxLibWrapper(true, CreateWindowTitle())),
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

//static
std::string WTen::CreateWindowTitle() {
	char str[1024];
	sprintf(str, "Wizardry Å`ìVó≥ÇÃìÉÅ` %s", OPEN_VERSION);
	return std::string(str);
}

boost::optional<boost::shared_ptr<Error> > WTen::DoStart() {
	bool initialize = true;
	while(scene) {
		if(initialize) {
			OPT_ERROR(scene->DoStart());
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
	if(!lib->ProcessMessage()) {
		return boost::shared_ptr<SceneExit>(new SceneExit());
	}
	OPT_ERROR(lib->ClearDrawScreen());
	LoopResult result = scene->DoNextFrame();
	OPT_ERROR(lib->ScreenFlip());
	return result;
}

} // wten

