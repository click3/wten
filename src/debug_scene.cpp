#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;

namespace {

boost::optional<boost::shared_ptr<Error> > AddUI(boost::shared_ptr<windows::WindowBase> window, boost::shared_ptr<const std::string> filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<Graph> src(new Graph(filename));
	boost::shared_ptr<uis::UIBase> ui(new uis::UIBox(src));
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddTextUI(const boost::shared_ptr<windows::WindowBase> window, boost::shared_ptr<const std::string> filename, boost::shared_ptr<const std::string> text, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
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

boost::optional<boost::shared_ptr<Error> > AddSelectorWindow(const boost::shared_ptr<WindowManager> manager, const boost::shared_ptr<std::string>& filename, const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& select_list, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!manager) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<windows::SelectWindow> window(new windows::SelectWindow(select_list, filename));
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	OPT_ERROR(manager->PushWindow(window));
	OPT_ERROR(window->Move(x, y));
	OPT_ERROR(window->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddQueueUI(const boost::shared_ptr<windows::WindowBase> window, boost::shared_ptr<const std::string> filename, const std::vector<boost::tuple<uis::UIQueue::POSITION, boost::shared_ptr<uis::UIBase> > >& ui_list, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<Graph> src(new Graph(filename));
	boost::shared_ptr<uis::UIBase> queue(new uis::UIQueue(ui_list));
	boost::shared_ptr<uis::UIBox> ui(new uis::UIBox(src));
	ui->SetInnerUI(queue);
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
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
	boost::shared_ptr<windows::WindowBase> window(new windows::WindowBase());
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	OPT_ERROR(window_manager->PushWindow(window));
	OPT_ERROR(window->Resize(640, 480));

	boost::shared_ptr<std::string> box(new std::string("data/ui/box1.png"));
	OPT_ERROR(AddUI(window, box, uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(window, box, boost::shared_ptr<std::string>(new std::string("��s�s�s�u�W�[�N�t�����g�v")), uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > select_list;
#define ADD_SELECT(text) select_list.push_back(boost::make_tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> >(boost::shared_ptr<std::string>(new std::string(text)), boost::shared_ptr<void>()))
	ADD_SELECT("�h���u���[�[�����C�f���v");
	ADD_SELECT("�x�X�g�o�����X�X");
	ADD_SELECT("�g�[�g���@");
	ADD_SELECT("����u���Z�M�v");
	ADD_SELECT("�W�[�N�t�����g�R�m�c����");
	ADD_SELECT("�V���̓��@�t��");
#undef ADD_SELECT
	OPT_ERROR(AddSelectorWindow(window_manager, box, select_list, 50, 100, 540, 150));

	std::vector<boost::tuple<uis::UIQueue::POSITION, boost::shared_ptr<uis::UIBase> > > ui_list;
#define ADD_UI(pos, text, width)																\
do {																				\
	boost::shared_ptr<std::string> str(new std::string(text));											\
	boost::shared_ptr<uis::UIBase> ui(new uis::UIString(str));											\
	OPT_ERROR(ui->Resize(width, 0));															\
	ui_list.push_back(boost::make_tuple<uis::UIQueue::POSITION, boost::shared_ptr<uis::UIBase> >(uis::UIQueue::COL_POSITION_##pos, ui));	\
} while(false)

	ADD_UI(LEFT, "���O", 100);
	ADD_UI(RIGHT, "�E��", 100);
	ADD_UI(RIGHT, "AC", 100);
	ADD_UI(RIGHT, "HP", 100);
	ADD_UI(RIGHT, "STATUS", 100);
#undef ADD_UI
	//OPT_ERROR(AddUI(window, box, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 320, 640, 160));
	OPT_ERROR(AddQueueUI(window, box, ui_list, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 320, 640, 160));
	return boost::none;
}

} // scenes

} // wten

