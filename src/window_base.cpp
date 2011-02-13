#include "stdafx.h"

namespace wten {

namespace windows {

using namespace utility;

WindowBase::WindowBase() :
	x(0),	y(0),	width(0),	height(0)
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

opt_error<boost::tuple<unsigned int, unsigned int> >::type WindowBase::GetPoint(void) {
	return boost::make_tuple<unsigned int, unsigned int>(x, y);
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type WindowBase::GetSize(void) {
	return boost::make_tuple<unsigned int, unsigned int>(width, height);
}

boost::optional<boost::shared_ptr<Error> > WindowBase::Move(unsigned int x, unsigned int y) {
	opt_error<boost::tuple<unsigned int, unsigned int> >::type opt_size = DxLibWrapper::GetWindowSize();
	if(opt_size.which() == 0) {
		boost::shared_ptr<Error> error = boost::get<boost::shared_ptr<Error> >(opt_size);
		return error;
	}
	unsigned int max_width;
	unsigned int max_height;
	boost::tie(max_width, max_height) = boost::get<boost::tuple<unsigned int, unsigned int> >(opt_size);

	if(x+width > max_width || y+height > max_height) {
		boost::shared_ptr<Error> error(new errors::ErrorNormal(ERROR_CODE_OUTSIDE_RANGE));
		return error;
	}
	this->x = x;
	this->y = y;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::Resize(unsigned int width, unsigned int height) {
	opt_error<boost::tuple<unsigned int, unsigned int> >::type opt_size = DxLibWrapper::GetWindowSize();
	if(opt_size.which() == 0) {
		boost::shared_ptr<Error> error = boost::get<boost::shared_ptr<Error> >(opt_size);
		return error;
	}
	unsigned int max_width;
	unsigned int max_height;
	boost::tie(max_width, max_height) = boost::get<boost::tuple<unsigned int, unsigned int> >(opt_size);

	if(x+width > max_width || y+height > max_height) {
		boost::shared_ptr<Error> error(new errors::ErrorNormal(ERROR_CODE_OUTSIDE_RANGE));
		return error;
	}
	this->width = width;
	this->height = height;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::Draw(void) {
	BOOST_FOREACH(boost::shared_ptr<UI> ui, ui_stack) {
		boost::optional<boost::shared_ptr<Error> > error = ui->Draw();
		if(error) {
			return error.get();
		}
	}
	return boost::none;
}

opt_error<boost::optional<boost::shared_ptr<Event> > >::type WindowBase::NotifyEvent(boost::shared_ptr<Event> event) {
	return event;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::AddUI(boost::shared_ptr<UI> ui) {
	ui_stack.push_back(ui);
	ui->SetOwnerWindow(this_ptr);
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
