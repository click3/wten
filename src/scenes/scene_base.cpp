#include "stdafx.h"

namespace wten { namespace scenes {

SceneBase::SceneBase(boost::shared_ptr<const std::string> default_frame_filename) :
	window_manager(new WindowManager()), base_window(new windows::WindowBase()), default_frame_filename(default_frame_filename)
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
	BOOST_ASSERT(ui);

	ui->SetMoveMode(move_mode);
	OPT_ERROR(base_window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	if(width == 0 && height == 0) {
		OPT_ERROR(ui->Resize());
	} else {
		OPT_ERROR(ui->Resize(width, height));
	}
	return boost::none;
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
	boost::shared_ptr<Graph> src(new Graph(default_frame_filename));
	boost::shared_ptr<uis::UIBase> ui(new uis::UIBox(src));
	return AddUI(ui, move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddTextUI(boost::shared_ptr<const std::string> text, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<uis::UIBase> ui(new uis::UIStringBox(default_frame_filename, text));
	return AddUI(ui, move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddPTStatusUI(boost::shared_ptr<const PTData> pt_data, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<uis::UIBase> ui(new uis::UIPTStatus(default_frame_filename, pt_data));
	return AddUI(ui, move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddSelectorWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& select_list, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<windows::SelectWindow> window(new windows::SelectWindow(select_list, default_frame_filename));
	return AddWindow(window, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddTextWindow(boost::shared_ptr<const std::string> text, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<windows::TextWindow> window(new windows::TextWindow(text, default_frame_filename));
	return AddWindow(window, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > SceneBase::AddInputDlgWindow(boost::shared_ptr<const std::string> message, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
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
