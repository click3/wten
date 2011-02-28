#include "stdafx.h"

namespace wten { namespace scenes {

namespace {

std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<Scene> > > CreateSceneList(void) {
	// TODO �K�؂ȃV�[���̐���
	std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<Scene> > > result;
	const char *text_list[] = {
		"�h���u���[�[�����C�f���v",
		"�x�X�g�o�����X�X",
		"�g�[�g���@",
		"����u���Z�M�v",
		"�`���҃M���h",
		"�W�[�N�t�����g�R�m�c����",
		"�V���̓��@�t��"
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
		boost::shared_ptr<const std::string> text(new std::string(text_list[i]));
		boost::shared_ptr<Scene> scene(scene_list[i]);
		result.push_back(make_tuple(text, scene));
	}
	return result;
}

boost::shared_ptr<const std::string> GetTownName(void) {
	// TODO
	return boost::shared_ptr<const std::string>(new std::string("��s�s�s�u�W�[�N�t�����g�v"));
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

