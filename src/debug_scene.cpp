#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

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

boost::optional<boost::shared_ptr<Error> > AddPTStatusUI(boost::shared_ptr<windows::WindowBase> window, boost::shared_ptr<const std::string> filename, boost::shared_ptr<const PTData> pt_data, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIPTStatus(filename, pt_data));
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
	OPT_ERROR(AddTextUI(window, box, boost::shared_ptr<std::string>(new std::string("城郭都市「ジークフロント」")), uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > select_list;
#define ADD_SELECT(text) select_list.push_back(boost::make_tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> >(boost::shared_ptr<std::string>(new std::string(text)), boost::shared_ptr<void>()))
	ADD_SELECT("宿屋「ローゼンメイデン」");
	ADD_SELECT("ベストバル商店街");
	ADD_SELECT("トート寺院");
	ADD_SELECT("酒場「超兄貴」");
	ADD_SELECT("ジークフロント騎士団兵舎");
	ADD_SELECT("天龍の塔　付近");
#undef ADD_SELECT
	OPT_ERROR(AddSelectorWindow(window_manager, box, select_list, 50, 100, 540, 150));

	OPT_ERROR(AddPTStatusUI(window, box, pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DebugScene::EnterFrame(void) {
	return boost::none;
}

} // scenes

} // wten

