#include "stdafx.h"

namespace wten {

namespace windows {

using namespace utility;

WindowBase::WindowBase() :
	x(0),	y(0),	width(640),	height(480)
{
}

//static
boost::shared_ptr<WindowBase> WindowBase::CreateWindowBase() {
	boost::shared_ptr<WindowBase> result(new WindowBase());
	BOOST_ASSERT(result);
	result->this_ptr = result;
	BOOST_ASSERT(result->this_ptr.lock());
	return result;
}

WindowBase::~WindowBase() {
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type WindowBase::GetPoint(void) const {
	return boost::make_tuple<unsigned int, unsigned int>(x, y);
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type WindowBase::GetSize(void) const {
	return boost::make_tuple<unsigned int, unsigned int>(width, height);
}

boost::optional<boost::shared_ptr<Error> > WindowBase::Move(unsigned int x, unsigned int y) {
	this->x = x;
	this->y = y;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::Resize(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::Draw(void) {
	unsigned int max_width;
	unsigned int max_height;
	OPT_PAIR_UINT(max_width, max_height, DxLibWrapper::GetWindowSize());

	if(x+width > max_width || y+height > max_height) {
		return CREATE_ERROR(ERROR_CODE_OUTSIDE_RANGE);
	}

	BOOST_FOREACH(boost::shared_ptr<UI> ui, ui_stack) {
		OPT_ERROR(ui->Draw());
	}
	return boost::none;
}

opt_error<boost::optional<boost::shared_ptr<Event> > >::type WindowBase::NotifyEvent(boost::shared_ptr<Event> event) {
	return event;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::AddUI(boost::shared_ptr<UI> ui) {
	ui_stack.push_back(ui);
	OPT_ERROR(ui->SetOwnerWindow(this_ptr));
	return boost::none;
}

opt_error<bool>::type WindowBase::RemoveUI(boost::shared_ptr<UI> ui) {
	std::vector<boost::shared_ptr<UI> >::iterator it = std::find(ui_stack.begin(), ui_stack.end(), ui);
	if(it == ui_stack.end()) {
		return false;
	}
	ui_stack.erase(it);
	return true;
}

} // windows

} // wten
