#include "stdafx.h"

namespace wten { namespace scenes {

using namespace utility;

SceneBase::SceneBase() :
	window_manager(new WindowManager())
{
}

SceneBase::~SceneBase() {
}

// static
boost::shared_ptr<Scene> SceneBase::CreateScene() {
	boost::shared_ptr<SceneBase> ptr(new SceneBase());
	BOOST_ASSERT(ptr);
	ptr->this_ptr = ptr;
	BOOST_ASSERT(ptr->this_ptr.lock());
	return ptr;
}

boost::optional<boost::shared_ptr<Error> > SceneBase::DoStart(void) {
	EventNotify::Regist(this_ptr);
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > SceneBase::DoNextFrame(void) {
	if(!window_manager) {
		return boost::shared_ptr<Error>(new errors::ErrorNormal(ERROR_CODE_INTERNAL_ERROR));
	}

	if(boost::optional<boost::shared_ptr<Error> > error = window_manager->DoEvent()) {
		return error.get();
	}

	if(boost::optional<boost::shared_ptr<Error> > error = window_manager->Draw()) {
		return error.get();
	}

	return boost::none;
}

void SceneBase::EventNotifyCallback(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(window_manager);
	window_manager->EnqueueEvent(event);
}

} // scenes

} // wten
