#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

namespace {

} // anonymous

DebugScene::DebugScene(void) {
}

boost::optional<boost::shared_ptr<Error> > DebugScene::SceneInitialize(void) {
	OPT_ERROR(AddBoxUI(uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(boost::shared_ptr<std::string>(new std::string("城郭都市「ジークフロント」")), uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > select_list;
#define ADD_SELECT(text) select_list.push_back(boost::make_tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> >(boost::shared_ptr<std::string>(new std::string(text)), boost::shared_ptr<void>()))
	ADD_SELECT("宿屋「ローゼンメイデン」");
	ADD_SELECT("ベストバル商店街");
	ADD_SELECT("トート寺院");
	ADD_SELECT("酒場「超兄貴」");
	ADD_SELECT("ジークフロント騎士団兵舎");
	ADD_SELECT("天龍の塔　付近");
#undef ADD_SELECT
	OPT_ERROR(AddSelectorWindow(select_list, 50, 100, 540, 150));

	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DebugScene::EnterFrame(void) {
	return boost::none;
}

} // scenes

} // wten

