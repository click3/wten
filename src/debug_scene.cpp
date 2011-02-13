#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;

DebugScene::DebugScene(void) {
}

boost::optional<boost::shared_ptr<Error> > DebugScene::DoStart(void) {
	boost::optional<boost::shared_ptr<Error> > error = SceneBase::DoStart();
	if(error) {
		return error.get();
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > DebugScene::SceneInitialize(void) {
	if(!window_manager) {
		return boost::shared_ptr<Error>(new errors::ErrorNormal(ERROR_CODE_INTERNAL_ERROR));
	}
	boost::shared_ptr<windows::WindowBase> window = windows::WindowBase::CreateWindowBase();
	if(!window) {
		return boost::shared_ptr<Error>(new errors::ErrorNormal(ERROR_CODE_INTERNAL_ERROR));
	}

	boost::optional<boost::shared_ptr<Error> > error = window_manager->PushWindow(window);
	if(error) {
		return error.get();
	}
	return boost::none;
}

} // scenes

} // wten

