#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

UIBox::UIBox(const std::string& filename) {
	BOOST_ASSERT(!filename.empty());

	boost::shared_ptr<Graph> src(new Graph(filename));
	BOOST_ASSERT(src);
	BOOST_ASSERT((src->GetWidth() % 2) == 1);
	BOOST_ASSERT(src->GetHeight() == src->GetHeight());

	const unsigned int corner_width = src->GetWidth() / 2;
	const unsigned int corner_height = src->GetHeight() / 2;
	const unsigned int line_len = 1;
	const unsigned int line_thick = src->GetWidth() / 2;
	const unsigned int blank_size = 1;
#define LOAD_DERIVATION(name, x, y, w, h) 									\
	{													\
		boost::optional<boost::shared_ptr<Graph>> name = src->Derivation(x, y, w, h);	\
		BOOST_ASSERT(name);										\
		this->name = name.get();									\
	}
	LOAD_DERIVATION(left_up,	0,				0,				corner_width,	corner_height);
	LOAD_DERIVATION(left_down,	0,				corner_height + line_len,	corner_width,	corner_height);
	LOAD_DERIVATION(right_up,	corner_width + line_len,	0,				corner_width,	corner_height);
	LOAD_DERIVATION(right_down,	corner_width + line_len,	corner_height + line_len,	corner_width,	corner_height);
	LOAD_DERIVATION(left_line,	0,				corner_height,		line_thick,	line_len);
	LOAD_DERIVATION(right_line,	corner_width + line_len,	corner_height,		line_thick,	line_len);
	LOAD_DERIVATION(up_line,	corner_width,			0,				line_len,	line_thick);
	LOAD_DERIVATION(down_line,	corner_width,			corner_height + line_len,	line_len,	line_thick);
	LOAD_DERIVATION(blank,	corner_width,			corner_height,		blank_size,	blank_size);
#undef LOAD_DERIVATION

	boost::optional<boost::shared_ptr<Error> > error = Resize(src->GetWidth(), src->GetHeight());
	BOOST_ASSERT(!error);
}

UIBox::~UIBox() {
}

boost::optional<boost::shared_ptr<Error> > UIBox::Resize(unsigned int width, unsigned int height) {
	if(width < left_up->GetWidth()+right_up->GetWidth() || height < left_up->GetHeight()+left_down->GetHeight()) {
		return CreateError(ERROR_CODE_OUTSIDE_RANGE);
	}
	return UIBase::Resize(width, height);
}

boost::optional<boost::shared_ptr<Error> > UIBox::Draw(void){
	BOOST_ASSERT(width >= left_up->GetWidth() + right_up->GetWidth());
	BOOST_ASSERT(height >= left_up->GetHeight() + left_down->GetHeight());

	const unsigned int bottom_x = x + width - right_up->GetWidth();
	const unsigned int bottom_y = y + height - left_down->GetHeight();
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = left_up->Draw(			x,		y)) {
		return error.get();
	}
	if(error = left_down->Draw(			x,		bottom_y)) {
		return error.get();
	}
	if(error = right_up->Draw(			bottom_x,	y)) {
		return error.get();
	}
	if(error = right_down->Draw(		bottom_x,	bottom_y)) {
		return error.get();
	}
	if(width > left_up->GetWidth() + right_up->GetWidth()) {
		const unsigned int line_x = x + left_up->GetWidth();
		const unsigned int line_len = width - left_up->GetWidth() - right_up->GetWidth();
		const unsigned int line_thick = left_up->GetHeight();
		if(error = up_line->DrawEx(		line_x,	y,		line_len,	line_thick)) {
			return error.get();
		}
		if(error = down_line->DrawEx(	line_x,	bottom_y,	line_len,	line_thick)) {
			return error.get();
		}
	}
	if(height > left_up->GetHeight() + left_down->GetHeight()) {
		const unsigned int line_y = y + left_up->GetHeight();
		const unsigned int line_len = height - left_up->GetHeight() - left_down->GetHeight();
		const unsigned int line_thick = left_up->GetWidth();
		if(error = left_line->DrawEx(	x,		line_y,	line_thick,	line_len)) {
			return error.get();
		}
		if(error = right_line->DrawEx(	bottom_x,	line_y,	line_thick,	line_len)) {
			return error.get();
		}
	}
	if(width > left_up->GetWidth() + right_up->GetWidth() && height > left_up->GetHeight() + left_down->GetHeight()) {
		const unsigned int blank_x = x + left_up->GetWidth();
		const unsigned int blank_y = y + left_up->GetHeight();
		const unsigned int blank_width = width - left_up->GetWidth() - right_up->GetWidth();
		const unsigned int blank_height = height - left_up->GetHeight() - left_down->GetHeight();
		if(error = blank->DrawEx(		blank_x,	blank_y,	blank_width,	blank_height)) {
			return error.get();
		}
	}
	return boost::none;
}

} // uis

} // wten
