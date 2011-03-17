#include "stdafx.h"

namespace wten { namespace scenes {

namespace {

std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<Scene> > > CreateSceneList(void) {
	// TODO 適切なシーンの生成
	std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<Scene> > > result;
	const wchar_t *text_list[] = {
		L"宿屋「ローゼンメイデン」",
		L"ベストバル商店街",
		L"トート寺院",
		L"酒場「超兄貴」",
		L"冒険者ギルド",
		L"ジークフロント騎士団兵舎",
		L"天龍の塔　付近"
	};
	boost::shared_ptr<Scene> scene_list[] = {
		boost::shared_ptr<Scene>(new scenes::HotelScene()),
		boost::shared_ptr<Scene>(new scenes::ShopScene()),
		boost::shared_ptr<Scene>(new scenes::TempleScene()),
		boost::shared_ptr<Scene>(new scenes::BarScene()),
		boost::shared_ptr<Scene>(new scenes::GuildScene()),
		boost::shared_ptr<Scene>(new scenes::CastleScene()),
		boost::shared_ptr<Scene>(new scenes::TowerGateScene())
	};
	for(unsigned int i = 0; i < 7; i++) {
		boost::shared_ptr<const std::wstring> text(new std::wstring(text_list[i]));
		boost::shared_ptr<Scene> scene(scene_list[i]);
		result.push_back(make_tuple(text, scene));
	}
	return result;
}

boost::shared_ptr<const std::wstring> GetTownName(void) {
	// TODO
	return boost::shared_ptr<const std::wstring>(new std::wstring(L"城郭都市「ジークフロント」"));
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

