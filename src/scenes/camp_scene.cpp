#include "stdafx.h"

namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

void CampScene::Initialize(void) {
	boost::optional<boost::shared_ptr<Error> > error;

	error = camp_script_window->AddEventProc(EVENT_TYPE_KEY, boost::bind(&CampScene::OnKeyEvent, this, _1));
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}

	error = camp_script_window->AddEventProc(EVENT_TYPE_NEXT_WINDOW, boost::bind(&CampScene::OnNextWindowEvent, this, _1));
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

CampScene::CampScene(boost::shared_ptr<const std::wstring> default_frame_filename) :
	SceneBase(default_frame_filename), camp_script_window(new windows::ScriptWindow()), camp_enabled(true)
{
	BOOST_ASSERT(camp_script_window);
	Initialize();
}

CampScene::CampScene(boost::shared_ptr<const Graph> default_frame_graph) :
	SceneBase(default_frame_graph), camp_script_window(new windows::ScriptWindow()), camp_enabled(true)
{
	BOOST_ASSERT(camp_script_window);
	Initialize();
}

CampScene::~CampScene() {
}

boost::optional<boost::shared_ptr<Error> > CampScene::SceneInitialize(void) {
	OPT_ERROR(AddWindow(camp_script_window, 0, 0, 0, 0));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampScene::OnKeyEvent(boost::shared_ptr<Event> event) {
	if(!camp_enabled) {
		return boost::none;
	}
	BOOST_ASSERT(event);
	BOOST_ASSERT(event->GetEventType() == EVENT_TYPE_KEY);
	boost::shared_ptr<events::KeyEvent> key = boost::static_pointer_cast<events::KeyEvent>(event);
	if(key->GetAction() == events::KeyEvent::KEY_PRESS) {
		switch(key->GetKey()) {
			case events::KeyEvent::KEY_Y:
				OPT_ERROR(AddCampWindow());
				return boost::none;
			default:
				break;
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampScene::OnNextWindowEvent(boost::shared_ptr<Event> event) {
	if(!camp_enabled) {
		return boost::none;
	}
	BOOST_ASSERT(event);
	BOOST_ASSERT(event->GetEventType() == EVENT_TYPE_NEXT_WINDOW);
	boost::shared_ptr<events::NextWindowEvent> next_window_event = boost::static_pointer_cast<events::NextWindowEvent>(event);
	boost::shared_ptr<Window> window = next_window_event->GetWindow();
	BOOST_ASSERT(window);
	OPT_ERROR(window_manager->PushWindow(window));
	return boost::none;
}


void CampScene::CampDisabled(void) {
	camp_enabled = false;
}

boost::optional<boost::shared_ptr<Error> > CampScene::AddCampWindow(void) {
	boost::shared_ptr<windows::CampWindow> camp(new windows::CampWindow(pt, default_frame_graph));
	OPT_ERROR(AddWindow(camp, 0, 0, 640, 480));
	return boost::none;
}

} // scenes

} // wten

