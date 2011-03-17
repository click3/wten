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
	OPT_ERROR(AddTextUI(boost::shared_ptr<std::wstring>(new std::wstring(L"デバッグモード")), uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));

	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DebugScene::EnterFrame(void) {
	return boost::shared_ptr<Scene>(new TownScene());
}

} // scenes

} // wten

