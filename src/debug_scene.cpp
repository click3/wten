#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

namespace {

} // anonymous

DebugScene::DebugScene(void) : SceneBase(WChar2Ptr(L"data/ui/box1.png")) {
}
DebugScene::~DebugScene() {
}

boost::optional<boost::shared_ptr<Error> > DebugScene::SceneInitialize(void) {
	OPT_ERROR(AddBoxUI(uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(boost::shared_ptr<std::wstring>(new std::wstring(L"デバッグモード")), uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	
	//PageSelectWindow(const std::vector<boost::tuple<boost::shared_ptr<uis::UIBase>, boost::shared_ptr<void> > >& input, unsigned int page_size, boost::shared_ptr<Graph> frame);
	std::vector<boost::tuple<boost::shared_ptr<uis::UIBase>, boost::shared_ptr<void> > > ui_list;
	const wchar_t *text_list[] = {
		L"クエストを受ける",
		L"クエストを報告する",
		L"聞き込みをする",
		L"寄付する",
		L"外に出る"
	};
	for(unsigned int i = 0; i < 5; i++) {
		boost::shared_ptr<uis::UIBase> ui(new uis::UIString(WChar2Ptr(text_list[i])));
		boost::shared_ptr<void> data(new int(0));
		ui_list.push_back(boost::make_tuple(ui, data));
	}
	boost::shared_ptr<windows::PageSelectWindow> window(new windows::PageSelectWindow(ui_list, 2, default_frame_graph));
	OPT_ERROR(AddWindow(window, 50, 100, 540, 180));
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DebugScene::EnterFrame(void) {
	return boost::none;//boost::shared_ptr<Scene>(new TownScene(default_frame_graph));
}

} // scenes

} // wten

