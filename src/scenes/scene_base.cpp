#include "stdafx.h"

namespace wten { namespace scenes {

SceneBase::SceneBase() :
	window_manager(new WindowManager()), base_window(new windows::WindowBase())
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

} // scenes

} // wten
