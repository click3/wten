#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;

namespace {

boost::optional<boost::shared_ptr<Error> > AddUI(const boost::shared_ptr<windows::WindowBase> window, const std::string& filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}
	if(filename.empty()) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIBox("data/ui/box1.png"));
	if(!ui) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = window->AddUI(ui)) {
		return error.get();
	}
	if(error = ui->Move(x, y)) {
		return error.get();
	}
	if(error = ui->Resize(width, height)) {
		return error.get();
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddTextUI(const boost::shared_ptr<windows::WindowBase> window, const std::string& filename, const std::string& text, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}
	if(filename.empty()) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIStringBox("data/ui/box1.png", text));
	if(!ui) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = window->AddUI(ui)) {
		return error.get();
	}
	if(error = ui->Move(x, y)) {
		return error.get();
	}
	if(error = ui->Resize(width, height)) {
		return error.get();
	}
	return boost::none;
}

} // anonymous

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
	boost::optional<boost::shared_ptr<Error> > error;
	if(!window_manager) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}
	boost::shared_ptr<windows::WindowBase> window = windows::WindowBase::CreateWindowBase();
	if(!window) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}
	if(error = window_manager->PushWindow(window)) {
		return error.get();
	}
	if(error = window->Resize(640, 480)) {
		return error.get();
	}

	if(error = AddUI(window, "data/ui/box1/box1.png", uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445)) {
		return error.get();
	}
	if(error = AddTextUI(window, "data/ui/box1/box1.png", "キャッスル：", uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32)) {
		return error.get();
	}
	if(error = AddUI(window, "data/ui/box1/box1.png", uis::UIBase::MOVE_MODE_FREE_FREE, 50, 100, 540, 150)) {
		return error.get();
	}
	if(error = AddUI(window, "data/ui/box1/box1.png", uis::UIBase::MOVE_MODE_FREE_FREE, 0, 320, 640, 160)) {
		return error.get();
	}
	return boost::none;
}

} // scenes

} // wten

