#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;

ScriptWindow::ScriptWindow() {
}

ScriptWindow::~ScriptWindow() {
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type ScriptWindow::GetPoint(void) {
	return boost::make_tuple<unsigned int, unsigned int>(0, 0);
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type ScriptWindow::GetSize(void) {
	return boost::make_tuple<unsigned int, unsigned int>(0, 0);
}

boost::optional<boost::shared_ptr<Error> > ScriptWindow::Move(unsigned int x, unsigned int y) {
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > ScriptWindow::Resize(unsigned int width, unsigned int height) {
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > ScriptWindow::Draw(void) {
	return boost::none;
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type ScriptWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	//TODO
	return boost::none;
}

} // windows

} // wten
