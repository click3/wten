#include "stdafx.h"
#include "version.h"

namespace wten {

WTen::WTen() :
	lib(new DxLibWrapper(true, CreateWindowTitle()))
{
	BOOST_ASSERT(lib);
	boost::optional<boost::shared_ptr<Error> > error = lib->SetDrawScreen(DxLibWrapper::SCREEN_MODE_BACK);
	if(error) {
		error.get()->Abort();
	}
}

WTen::~WTen() {
}

//static
boost::shared_ptr<std::wstring> WTen::CreateWindowTitle(void) {
	wchar_t str[1024];
	WSPRINTF(str, L"Wizardry Å`ìVó≥ÇÃìÉÅ` %s", OPEN_VERSION);
	return boost::shared_ptr<std::wstring>(new std::wstring(str));
}

void WTen::SetScene(boost::shared_ptr<Scene> scene) {
	this->scene = scene;
}

boost::shared_ptr<Scene> WTen::GetScene(void) {
	return scene;
}

boost::shared_ptr<const Scene> WTen::GetScene(void) const {
	return scene;
}

boost::optional<boost::shared_ptr<Error> > WTen::DoStart(boost::shared_ptr<PTData> pt) {
	bool initialize = true;
	while(scene) {
		if(initialize) {
			OPT_ERROR(scene->DoStart(pt));
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

