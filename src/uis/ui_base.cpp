#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

namespace {

boost::optional<boost::shared_ptr<Error> > OwnerRectCheck(const boost::weak_ptr<windows::WindowBase> owner, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<windows::WindowBase> window = owner.lock();
	if(!window) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}

	unsigned int owner_width;
	unsigned int owner_height;
	{
		opt_error<boost::tuple<unsigned int, unsigned int> >::type owner_size = window->GetSize();
		if(owner_size.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(owner_size);
		}
		boost::tie(owner_width, owner_height) = boost::get<boost::tuple<unsigned int, unsigned int> >(owner_size);
	}

	if(x+width > owner_width || y+height > owner_height) {
		return CreateError(ERROR_CODE_OUTSIDE_RANGE);
	}
	return boost::none;
}

} // anonymous

UIBase::UIBase() :
	x(0),	y(0),	width(0),	height(0),	move_mode(MOVE_MODE_FREE_FREE)
{
}

UIBase::~UIBase() {
}

boost::optional<boost::shared_ptr<Error> > UIBase::SetOwnerWindow(boost::weak_ptr<windows::WindowBase> window) {
	if(owner.lock()) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}
	owner = window;
	BOOST_ASSERT(owner.lock());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBase::InnerRectCheck(void) {
	opt_error<unsigned int>::type width = CalcWidth();
	if(width.which() == 0) {
		return boost::get<boost::shared_ptr<Error> >(width);
	}
	opt_error<unsigned int>::type height = CalcHeight();
	if(height.which() == 0) {
		return boost::get<boost::shared_ptr<Error> >(height);
	}
	if(this->width < boost::get<unsigned int>(width) || this->height < boost::get<unsigned int>(height)) {
		return CreateError(ERROR_CODE_OUTSIDE_RANGE);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBase::PointAndSizeIsValid(void) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = InnerRectCheck()) {
		if(error = Resize()) {
			return error.get();
		}
		if(error = InnerRectCheck()) {
			return error.get();
		}
	}
	if(error = OwnerRectCheck(owner, x, y, width, height)) {
		if(error = Move()) {
			return error.get();
		}
		if(error = OwnerRectCheck(owner, x, y, width, height)) {
			return error.get();
		}
	}
	return boost::none;
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type UIBase::GetPoint(void) {
	return boost::make_tuple<unsigned int, unsigned int>(x, y);
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type UIBase::GetAbsolutePoint(void) {
	boost::shared_ptr<windows::WindowBase> window = owner.lock();
	if(!window) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}
	opt_error<boost::tuple<unsigned int, unsigned int> >::type owner_point = window->GetPoint();
	if(owner_point.which() == 0) {
		return boost::get<boost::shared_ptr<Error> >(owner_point);
	}
	unsigned int owner_x;
	unsigned int owner_y;
	boost::tie(owner_x, owner_y) = boost::get<boost::tuple<unsigned int, unsigned int> >(owner_point);
	return boost::make_tuple<unsigned int, unsigned int>(owner_x + x, owner_y + y);
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type UIBase::GetSize(void) {
	return boost::make_tuple<unsigned int, unsigned int>(width, height);
}

void UIBase::SetMoveMode(MOVE_MODE move_mode) {
	this->move_mode = move_mode;
}

UIBase::MOVE_MODE UIBase::GetMoveMode(void) {
	return this->move_mode;
}

boost::optional<boost::shared_ptr<Error> > UIBase::Move() {
	unsigned int owner_width;
	unsigned int owner_height;
	{
		boost::shared_ptr<windows::WindowBase> window = owner.lock();
		if(!window) {
			return CreateError(ERROR_CODE_INTERNAL_ERROR);
		}
		opt_error<boost::tuple<unsigned int, unsigned int> >::type owner_size = window->GetSize();
		if(owner_size.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(owner_size);
		}
		boost::tie(owner_width, owner_height) = boost::get<boost::tuple<unsigned int, unsigned int> >(owner_size);
	}

	switch(move_mode) {
		case MOVE_MODE_LEFT_UP:
		case MOVE_MODE_LEFT_CENTER:
		case MOVE_MODE_LEFT_DOWN:
		case MOVE_MODE_LEFT_FREE: {
			x = 0;
			break;
		}
		case MOVE_MODE_CENTER_UP:
		case MOVE_MODE_CENTER_CENTER:
		case MOVE_MODE_CENTER_DOWN:
		case MOVE_MODE_CENTER_FREE: {
			x = (owner_width - width) / 2;
			break;
		}
		case MOVE_MODE_FREE_UP:
		case MOVE_MODE_FREE_CENTER:
		case MOVE_MODE_FREE_DOWN:
		case MOVE_MODE_FREE_FREE: {
			if(x+width <= owner_width) {
				break;
			}
		}
		case MOVE_MODE_RIGHT_UP:
		case MOVE_MODE_RIGHT_CENTER:
		case MOVE_MODE_RIGHT_DOWN:
		case MOVE_MODE_RIGHT_FREE: {
			x = owner_width - width;
			break;
		}
	}

	switch(move_mode) {
		case MOVE_MODE_LEFT_UP:
		case MOVE_MODE_CENTER_UP:
		case MOVE_MODE_RIGHT_UP:
		case MOVE_MODE_FREE_UP: {
			y = 0;
			break;
		}
		case MOVE_MODE_LEFT_CENTER:
		case MOVE_MODE_CENTER_CENTER:
		case MOVE_MODE_RIGHT_CENTER:
		case MOVE_MODE_FREE_CENTER: {
			y = (owner_height - height) / 2;
			break;
		}
		case MOVE_MODE_LEFT_FREE:
		case MOVE_MODE_CENTER_FREE:
		case MOVE_MODE_RIGHT_FREE:
		case MOVE_MODE_FREE_FREE: {
			if(y+height <= owner_height) {
				break;
			}
		}
		case MOVE_MODE_LEFT_DOWN:
		case MOVE_MODE_CENTER_DOWN:
		case MOVE_MODE_RIGHT_DOWN:
		case MOVE_MODE_FREE_DOWN: {
			x = owner_height - height;
			break;
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBase::Move(unsigned int x, unsigned int y) {
	this->x = x;
	this->y = y;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBase::AbsoluteMove(unsigned int x, unsigned int y) {
	boost::shared_ptr<windows::WindowBase> window = owner.lock();
	if(!window) {
		return CreateError(ERROR_CODE_INTERNAL_ERROR);
	}
	opt_error<boost::tuple<unsigned int, unsigned int> >::type owner_point = window->GetPoint();
	if(owner_point.which() == 0) {
		return boost::get<boost::shared_ptr<Error> >(owner_point);
	}
	unsigned int owner_x;
	unsigned int owner_y;
	boost::tie(owner_x, owner_y) = boost::get<boost::tuple<unsigned int, unsigned int> >(owner_point);
	if(x < owner_x || y < owner_y) {
		return CreateError(ERROR_CODE_OUTSIDE_RANGE);
	}
	return Move(x-owner_x, y-owner_y);
}

boost::optional<boost::shared_ptr<Error> > UIBase::Resize(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBase::Resize(void) {
	opt_error<unsigned int>::type width = CalcWidth();
	if(width.which() == 0) {
		return boost::get<boost::shared_ptr<Error> >(width);
	}
	opt_error<unsigned int>::type height = CalcHeight();
	if(height.which() == 0) {
		return boost::get<boost::shared_ptr<Error> >(height);
	}
	const unsigned int w = std::max(this->width, boost::get<unsigned int>(width));
	const unsigned int h = std::max(this->height, boost::get<unsigned int>(height));
	boost::optional<boost::shared_ptr<Error> > error = Resize(w, h);
	if(error) {
		return error.get();
	}
	return boost::none;
}

utility::opt_error<unsigned int>::type UIBase::CalcWidth() {
	return 0;
}

utility::opt_error<unsigned int>::type UIBase::CalcHeight() {
	return 0;
}

} // uis

} // wten
