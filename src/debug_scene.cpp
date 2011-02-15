#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;

namespace {

boost::optional<boost::shared_ptr<Error> > AddUI(const boost::shared_ptr<windows::WindowBase> window, const boost::shared_ptr<std::string>& filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIBox(filename));
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddTextUI(const boost::shared_ptr<windows::WindowBase> window, const boost::shared_ptr<std::string>& filename, const boost::shared_ptr<std::string>& text, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIStringBox(filename, text));
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddImageUI(const boost::shared_ptr<windows::WindowBase> window, const boost::shared_ptr<std::string>& filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIImage(filename));
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddSelectorWindow(const boost::shared_ptr<WindowManager> manager, const std::vector<boost::tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> > >& select_list, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!manager) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<windows::SelectWindow> window = windows::SelectWindow::CreateSelectWindow(select_list);
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	OPT_ERROR(manager->PushWindow(window));
	OPT_ERROR(window->Move(x, y));
	OPT_ERROR(window->Resize(width, height));
	return boost::none;
}

} // anonymous

DebugScene::DebugScene(void) {
}

boost::optional<boost::shared_ptr<Error> > DebugScene::DoStart(void) {
	OPT_ERROR(SceneBase::DoStart());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > DebugScene::SceneInitialize(void) {
	if(!window_manager) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	boost::shared_ptr<windows::WindowBase> window = windows::WindowBase::CreateWindowBase();
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	OPT_ERROR(window_manager->PushWindow(window));
	OPT_ERROR(window->Resize(640, 480));

	boost::shared_ptr<std::string> box(new std::string("data/ui/box1.png"));
	OPT_ERROR(AddUI(window, box, uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddImageUI(window, boost::shared_ptr<std::string>(new std::string("data/ui/arrow1.png")), uis::UIBase::MOVE_MODE_FREE_FREE, 235, 15, 20, 20));
	OPT_ERROR(AddTextUI(window, box, boost::shared_ptr<std::string>(new std::string("キャッスル：")), uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	std::vector<boost::tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> > > select_list;
#define ADD_SELECT(text) select_list.push_back(boost::make_tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> >(boost::shared_ptr<std::string>(new std::string(text)), boost::shared_ptr<void>()))
	ADD_SELECT("ギルガメッシュの酒場");
	ADD_SELECT("冒険者の宿");
	ADD_SELECT("ボルタック商店");
	ADD_SELECT("カント寺院");
	ADD_SELECT("町外れ");
#undef ADD_SELECT
	OPT_ERROR(AddSelectorWindow(window_manager, select_list, 50, 100, 540, 150));
	OPT_ERROR(AddUI(window, box, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 320, 640, 160));
	return boost::none;
}

} // scenes

} // wten

