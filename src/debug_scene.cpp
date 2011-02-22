#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

namespace {

} // anonymous

DebugScene::DebugScene(void) {
}
DebugScene::~DebugScene() {
}

boost::optional<boost::shared_ptr<Error> > DebugScene::SceneInitialize(void) {
	OPT_ERROR(AddBoxUI(uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(boost::shared_ptr<std::string>(new std::string("�f�o�b�O���[�h")), uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));
	const char char_text[] =
		"�ЂƂ�̋����ȃh���[�t������č�����\n"
		"\n"
		"���� ���߂łƂ� ����\n"
		"\n"
		"���݂����͑�N��g���{�[�̎����ɍ��i�����B\n"
		"\n"
		"���[�h�i�̖����������߂������Ƃɂ��A\n"
		"�g���{�[�͏��N�� 50,000 �̌o���l�Ƌ���^����������\n"
		"���N���߉q���̏��Z�ɔC�����܂����B\n"
		"\n"
		"�ւ�������ĊK����(>)��t����悤�ɁB\n"
		"\n"
		"�������A���N�͍X�Ȃ�b�B�𑱂��Ȃ��Ă͂Ȃ�Ȃ��B\n"
		"�g���{�[�͌���Ȃ����x���̍����q����K�v�Ƃ��Ă���̂ł��B\n"
		"\n"
		"�����Ă���́c\n"
		"�V���Ȃ�`���ւ̏����ł�����̂ł��B";
	boost::shared_ptr<std::string> text(new std::string(char_text));
	OPT_ERROR(AddTextWindow(text, 50, 50, 540, 380));

	boost::shared_ptr<std::string> message(new std::string("�M���h������͂��Ă�������"));
	boost::shared_ptr<uis::UIBase> ui(new uis::UIInputDlg(message, default_frame_filename));
	OPT_ERROR(AddUI(ui, uis::UIBase::MOVE_MODE_CENTER_CENTER, 10, 25, 0, 0));
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DebugScene::EnterFrame(void) {
	return boost::none;
}

} // scenes

} // wten

