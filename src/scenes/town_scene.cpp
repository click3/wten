#include "stdafx.h"

namespace wten { namespace scenes {

namespace {

std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<Scene> > > CreateSceneList(void) {
	// TODO 適切なシーンの生成
	std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<Scene> > > result;
	const char *text_list[] = {
		"宿屋「ローゼンメイデン」",
		"ベストバル商店街",
		"トート寺院",
		"酒場「超兄貴」",
		"ジークフロント騎士団兵舎",
		"天龍の塔　付近"
	};
	boost::shared_ptr<Scene> scene_list[] = {
		boost::shared_ptr<Scene>(new scenes::DebugScene()),
		boost::shared_ptr<Scene>(new scenes::DebugScene()),
		boost::shared_ptr<Scene>(new scenes::DebugScene()),
		boost::shared_ptr<Scene>(new scenes::BarScene()),
		boost::shared_ptr<Scene>(new scenes::CastleScene()),
		boost::shared_ptr<Scene>(new scenes::TowerGateScene())
	};
	for(unsigned int i = 0; i < 6; i++) {
		boost::shared_ptr<const std::string> text(new std::string(text_list[i]));
		boost::shared_ptr<Scene> scene(scene_list[i]);
		result.push_back(make_tuple(text, scene));
	}
	return result;
}

boost::shared_ptr<const std::string> GetTownName(void) {
	// TODO
	return boost::shared_ptr<const std::string>(new std::string("城郭都市「ジークフロント」"));
}

} // anonymous


TownScene::TownScene() :
	SceneSelectorScene(GetTownName(), CreateSceneList())
{
}

TownScene::~TownScene() {
}

} // scenes

} // wten

