#include "stdafx.h"

namespace wten { namespace scenes {

SceneBase::SceneBase() :
	window_manager(new WindowManager())
{
}

SceneBase::~SceneBase() { }

boost::optional<boost::shared_ptr<Error> > SceneBase::DoStart(void) {
	boost::shared_ptr<SceneBase> this_ptr = shared_from_this();
	BOOST_ASSERT(this_ptr);
	EventNotify::Regist(this_ptr);
	OPT_ERROR(this_ptr->SceneInitialize());
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > SceneBase::DoNextFrame(void) {
	BOOST_ASSERT(window_manager);
	OPT_ERROR(window_manager->DoEvent());
	OPT_ERROR(window_manager->Draw());
	return boost::none;
}
void SceneBase::EventNotifyCallback(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(window_manager);
	if(boost::optional<boost::shared_ptr<Error> > error = window_manager->EnqueueEvent(event)) {
		error.get()->Abort();
	}
}

boost::optional<boost::shared_ptr<Error> > SceneBase::SceneInitialize(void) {
	return boost::none;
}

} // scenes

} // wten
