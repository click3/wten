#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

namespace {

boost::optional<boost::shared_ptr<Error> > OwnerRectCheck(boost::weak_ptr<const windows::WindowBase> owner, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<const windows::WindowBase> window = owner.lock();
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}

	unsigned int owner_width;
	unsigned int owner_height;
	OPT_PAIR_UINT(owner_width, owner_height, window->GetSize());

	if(x+width > owner_width || y+height > owner_height) {
		return CREATE_ERROR(ERROR_CODE_OUTSIDE_RANGE);
	}
	return boost::none;
}

} // anonymous

UIBase::UIBase() :
	x(0),	y(0),	width(0),	height(0),	move_mode(MOVE_MODE_FREE_FREE), visible(true)
{
}

UIBase::~UIBase() {
}

boost::optional<boost::shared_ptr<Error> > UIBase::SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window) {
	if(!window.lock()) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(owner.lock()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	owner = window;
	BOOST_ASSERT(owner.lock());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBase::ClearOwnerWindow(void) {
	owner.reset();
	BOOST_ASSERT(!owner.lock());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBase::InnerRectCheck(void) {
	unsigned int width;
	OPT_UINT(width, CalcWidth());
	unsigned int height;
	OPT_UINT(height, CalcHeight());

	if(this->width < width || this->height < height) {
		return CREATE_ERROR(ERROR_CODE_OUTSIDE_RANGE);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBase::PointAndSizeIsValid(void) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = InnerRectCheck()) {
		OPT_ERROR(Resize());
		OPT_ERROR(InnerRectCheck());
	}
	if(error = OwnerRectCheck(owner, x, y, width, height)) {
		OPT_ERROR(Move());
		OPT_ERROR(OwnerRectCheck(owner, x, y, width, height));
	}
	return boost::none;
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type UIBase::GetPoint(void) const {
	return boost::make_tuple<unsigned int, unsigned int>(x, y);
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type UIBase::GetAbsolutePoint(void) const {
	boost::shared_ptr<const windows::WindowBase> window = owner.lock();
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	unsigned int owner_x;
	unsigned int owner_y;
	OPT_PAIR_UINT(owner_x, owner_y, window->GetPoint());
	return boost::make_tuple<unsigned int, unsigned int>(owner_x + x, owner_y + y);
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type UIBase::GetSize(void) const {
	return boost::make_tuple<unsigned int, unsigned int>(width, height);
}

bool UIBase::IsVisible(void) const {
	return visible;
}

void UIBase::SetVisible(bool flag) {
	visible = flag;
}

boost::optional<boost::shared_ptr<Error> > UIBase::Draw(void) {
	if(!visible) {
		return boost::none;
	}
	OPT_ERROR(PointAndSizeIsValid());
	OPT_ERROR(Move());

	unsigned int x;
	unsigned int y;
	OPT_PAIR_UINT(x, y, GetAbsolutePoint());
	return Draw(x, y);
}

void UIBase::SetMoveMode(MOVE_MODE move_mode) {
	this->move_mode = move_mode;
}

UIBase::MOVE_MODE UIBase::GetMoveMode(void) const {
	return move_mode;
}

boost::optional<boost::shared_ptr<Error> > UIBase::Move() {
	boost::shared_ptr<const windows::WindowBase> window = owner.lock();
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	unsigned int owner_width;
	unsigned int owner_height;
	OPT_PAIR_UINT(owner_width, owner_height, window->GetSize());

	unsigned int x = this->x;
	unsigned int y = this->y;
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
	return Move(x, y);
}

boost::optional<boost::shared_ptr<Error> > UIBase::Move(unsigned int x, unsigned int y) {
	this->x = x;
	this->y = y;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBase::AbsoluteMove(unsigned int x, unsigned int y) {
	boost::shared_ptr<const windows::WindowBase> window = owner.lock();
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	unsigned int owner_x;
	unsigned int owner_y;
	OPT_PAIR_UINT(owner_x, owner_y, window->GetPoint());
	if(x < owner_x || y < owner_y) {
		return CREATE_ERROR(ERROR_CODE_OUTSIDE_RANGE);
	}
	return Move(x-owner_x, y-owner_y);
}

boost::optional<boost::shared_ptr<Error> > UIBase::Resize(unsigned int width, unsigned int height) {
	unsigned int min_width;
	unsigned int min_height;
	OPT_UINT(min_width, CalcWidth());
	OPT_UINT(min_height, CalcHeight());
	if(width < min_width || height < min_height) {
		this->width = std::max(width, min_width);
		this->height = std::max(height, min_height);
		return boost::none;
	}
	this->width = width;
	this->height = height;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBase::Resize(void) {
	unsigned int width;
	unsigned int height;
	OPT_UINT(width, CalcWidth());
	OPT_UINT(height, CalcHeight());

	const unsigned int w = std::max(this->width, width);
	const unsigned int h = std::max(this->height, height);

	OPT_ERROR(Resize(w, h));

	return boost::none;
}

utility::opt_error<unsigned int>::type UIBase::CalcWidth() const {
	return 0;
}

utility::opt_error<unsigned int>::type UIBase::CalcHeight() const {
	return 0;
}

} // uis

} // wten
