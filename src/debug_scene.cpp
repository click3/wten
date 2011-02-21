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
	OPT_ERROR(AddTextUI(boost::shared_ptr<std::string>(new std::string("��s�s�s�u�W�[�N�t�����g�v")), uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > select_list;
#define ADD_SELECT(text) select_list.push_back(boost::make_tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> >(boost::shared_ptr<std::string>(new std::string(text)), boost::shared_ptr<void>()))
	ADD_SELECT("�h���u���[�[�����C�f���v");
	ADD_SELECT("�x�X�g�o�����X�X");
	ADD_SELECT("�g�[�g���@");
	ADD_SELECT("����u���Z�M�v");
	ADD_SELECT("�W�[�N�t�����g�R�m�c����");
	ADD_SELECT("�V���̓��@�t��");
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

