#include "stdafx.h"

namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

SceneBase::SceneBase(boost::shared_ptr<const std::wstring> default_frame_filename) :
	window_manager(new WindowManager()), base_window(new windows::WindowBase(default_frame_filename)), default_frame_filename(default_frame_filename)
{
	BOOST_ASSERT(window_manager);
	BOOST_ASSERT(base_window);

	boost::optional<boost::shared_ptr<Error> > error;
	if(error = window_manager->PushWindow(base_window)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	if(error = base_window->Resize(640, 480)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

SceneBase::~SceneBase() { }

boost::optional<boost::shared_ptr<Error> > SceneBase::DoStart(boost::shared_ptr<PTData> pt) {
	if(!pt) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	this->pt = pt;

	boost::shared_ptr<SceneBase> this_ptr = shared_from_this();
	BOOST_ASSERT(this_ptr);
	EventNotify::Regist(this_ptr);

	OPT_ERROR(Clear());
	OPT_ERROR(this_ptr->SceneInitialize());
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > SceneBase::DoNextFrame(void) {
	BOOST_ASSERT(window_manager);
	OPT_ERROR(window_manager->DoEvent());
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > result;
	result = EnterFrame();
	if(result.which() == 1) {
		OPT_ERROR(window_manager->Draw());
	}
	return result;
}
void SceneBase::EventNotifyCallback(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(window_manager);
	if(boost::optional<boost::shared_ptr<Error> > error = window_manager->EnqueueEvent(event)) {
		error.get()->Abort();
	}
}



boost::optional<boost::shared_ptr<Error> > SceneBase::AddUI(boost::shared_ptr<uis::UIBase> ui, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	BOOST_ASSERT(base_window);
	return base_window->AddUI(ui, move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddWindow(boost::shared_ptr<windows::WindowBase> window, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	BOOST_ASSERT(window_manager);
	BOOST_ASSERT(window);

	OPT_ERROR(window_manager->PushWindow(window));
	OPT_ERROR(window->Move(x, y));
	OPT_ERROR(window->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddBoxUI(uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	BOOST_ASSERT(base_window);
	return base_window->AddBoxUI(move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddImageUI(boost::shared_ptr<const std::wstring> image_filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y) {
	BOOST_ASSERT(base_window);
	return base_window->AddImageUI(image_filename, move_mode, x, y);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddTextUI(boost::shared_ptr<const std::wstring> text, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	BOOST_ASSERT(base_window);
	return base_window->AddTextUI(text, move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddPTStatusUI(boost::shared_ptr<const PTData> pt_data, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	BOOST_ASSERT(base_window);
	return base_window->AddPTStatusUI(pt_data, move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddCharStatusUI(boost::shared_ptr<const PTData> pt_data, unsigned int char_index, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	BOOST_ASSERT(base_window);
	return base_window->AddCharStatusUI(pt_data, char_index, move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddSelectorWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > >& select_list, unsigned int line_count, boost::optional<unsigned int> cancel_index, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<windows::SelectWindow> window(new windows::SelectWindow(select_list, line_count, default_frame_filename));
	OPT_ERROR(window->SetCancelSelectionDataIndex(cancel_index));
	return AddWindow(window, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddTextWindow(boost::shared_ptr<const std::wstring> text, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<windows::TextWindow> window(new windows::TextWindow(text, default_frame_filename));
	return AddWindow(window, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddInputDlgWindow(boost::shared_ptr<const std::wstring> message, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<windows::InputDlgWindow> window(new windows::InputDlgWindow(message, default_frame_filename));
	return AddWindow(window, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::Clear(void) {
	OPT_ERROR(window_manager->Clear());
	OPT_ERROR(base_window->ClearUI());
	return window_manager->PushWindow(base_window);
}

} // scenes

} // wten
