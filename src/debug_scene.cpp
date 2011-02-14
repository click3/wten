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
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = window->AddUI(box)) {
		return error.get();
	}
	if(error = box->Move(x, y)) {
		return error.get();
	}
	if(error = box->Resize(width, height)) {
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
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	boost::shared_ptr<windows::WindowBase> window = windows::WindowBase::CreateWindowBase();
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(error = window_manager->PushWindow(window)) {
		return error.get();
	}
	if(error = window->Resize(640, 480)) {
		return error.get();
	}

	if(error = AddUI(window, "data/ui/box1.png", uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445)) {
		return error.get();
	}
	if(error = AddImageUI(window, "data/ui/arrow1.png", uis::UIBase::MOVE_MODE_FREE_FREE, 235, 15, 20, 20)) {
		return error.get();
	}
	if(error = AddTextUI(window, "data/ui/box1.png", "�L���b�X���F", uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32)) {
		return error.get();
	}
	std::vector<std::string> select_list;
	select_list.push_back("�M���K���b�V���̎���");
	select_list.push_back("�`���҂̏h");
	select_list.push_back("�{���^�b�N���X");
	select_list.push_back("�J���g���@");
	select_list.push_back("���O��");
	if(error = AddSelectorUI(window, "data/ui/box1.png", select_list, uis::UIBase::MOVE_MODE_FREE_FREE, 50, 100, 540, 150)) {
		return error.get();
	}
	if(error = AddUI(window, "data/ui/box1.png", uis::UIBase::MOVE_MODE_FREE_FREE, 0, 320, 640, 160)) {
		return error.get();
	}
	return boost::none;
}

} // scenes

} // wten

