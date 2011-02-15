#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;

namespace {

boost::optional<boost::shared_ptr<Error> > AddUI(const boost::shared_ptr<windows::WindowBase> window, const std::string& filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(filename.empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIBox(filename.c_str()));
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddTextUI(const boost::shared_ptr<windows::WindowBase> window, const std::string& filename, const std::string& text, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(filename.empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIStringBox(filename.c_str(), text));
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddImageUI(const boost::shared_ptr<windows::WindowBase> window, const std::string& filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(filename.empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIImage(filename.c_str()));
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddSelectorUI(const boost::shared_ptr<windows::WindowBase> window, const std::string& filename, const std::vector<std::string>& select_list, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(filename.empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBox> box(new uis::UIBox(filename.c_str()));
	boost::shared_ptr<uis::UIBase> selector(new uis::UISelector(select_list));
	if(!box || !selector) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	box->SetInnerUI(selector);
	box->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(box));
	OPT_ERROR(box->Move(x, y));
	OPT_ERROR(box->Resize(width, height));
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

	OPT_ERROR(AddUI(window, "data/ui/box1.png", uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddImageUI(window, "data/ui/arrow1.png", uis::UIBase::MOVE_MODE_FREE_FREE, 235, 15, 20, 20));
	OPT_ERROR(AddTextUI(window, "data/ui/box1.png", "キャッスル：", uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	std::vector<std::string> select_list;
	select_list.push_back("ギルガメッシュの酒場");
	select_list.push_back("冒険者の宿");
	select_list.push_back("ボルタック商店");
	select_list.push_back("カント寺院");
	select_list.push_back("町外れ");
	OPT_ERROR(AddSelectorUI(window, "data/ui/box1.png", select_list, uis::UIBase::MOVE_MODE_FREE_FREE, 50, 100, 540, 150));
	OPT_ERROR(AddUI(window, "data/ui/box1.png", uis::UIBase::MOVE_MODE_FREE_FREE, 0, 320, 640, 160));
	return boost::none;
}

} // scenes

} // wten

