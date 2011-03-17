#include "stdafx.h"

namespace wten { namespace scenes {

namespace {

std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<Scene> > > CreateSceneList(void) {
	// TODO �K�؂ȃV�[���̐���
	std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<Scene> > > result;
	const wchar_t *text_list[] = {
		L"�h���u���[�[�����C�f���v",
		L"�x�X�g�o�����X�X",
		L"�g�[�g���@",
		L"����u���Z�M�v",
		L"�`���҃M���h",
		L"�W�[�N�t�����g�R�m�c����",
		L"�V���̓��@�t��"
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
	return boost::shared_ptr<const std::wstring>(new std::wstring(L"��s�s�s�u�W�[�N�t�����g�v"));
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

