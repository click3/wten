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
	OPT_ERROR(AddTextUI(boost::shared_ptr<std::string>(new std::string("デバッグモード")), uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));
	const char char_text[] =
		"ひとりの屈強なドワーフが現れて告げた\n"
		"\n"
		"＊＊ おめでとう ＊＊\n"
		"\n"
		"きみたちは大君主トレボーの試験に合格した。\n"
		"\n"
		"ワードナの魔除けを取り戻したことにより、\n"
		"トレボーは諸君に 50,000 の経験値と金を与えたうえに\n"
		"諸君を近衛兵の将校に任命しました。\n"
		"\n"
		"誇りを持って階級章(>)を付けるように。\n"
		"\n"
		"ただし、諸君は更なる鍛錬を続けなくてはならない。\n"
		"トレボーは限りなくレベルの高い衛兵を必要としているのです。\n"
		"\n"
		"そしてそれは…\n"
		"新たなる冒険への準備でもあるのです。";
	boost::shared_ptr<std::string> text(new std::string(char_text));
	OPT_ERROR(AddTextWindow(text, 50, 50, 540, 380));

	boost::shared_ptr<std::string> message(new std::string("ギルド名を入力してください"));
	boost::shared_ptr<uis::UIBase> ui(new uis::UIInputDlg(message, default_frame_filename));
	OPT_ERROR(AddUI(ui, uis::UIBase::MOVE_MODE_CENTER_CENTER, 10, 25, 0, 0));
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DebugScene::EnterFrame(void) {
	return boost::none;
}

} // scenes

} // wten

