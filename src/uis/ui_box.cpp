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
#define LOAD_DERIVATION(name, x, y, w, h) 								\
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

	width = src->GetWidth();
	height = src->GetHeight();
}

UIBox::~UIBox() {
}

boost::optional<boost::shared_ptr<Error> > UIBox::SetOwnerWindow(boost::weak_ptr<windows::WindowBase> window) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = UIBase::SetOwnerWindow(window)) {
		return error.get();
	}
	if(inner_ui) {
		if(error = inner_ui->SetOwnerWindow(window)) {
			return error.get();
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBox::Move(void) {
	return UIBase::Move();
}

boost::optional<boost::shared_ptr<Error> > UIBox::Move(unsigned int x, unsigned int y) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = UIBase::Move(x, y)) {
		return error.get();
	}
	if(inner_ui) {
		const unsigned int inner_x = x + left_up->GetWidth();
		const unsigned int inner_y = y + left_up->GetHeight();
		if(error = inner_ui->Move(inner_x, inner_y)) {
			return error.get();
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBox::Resize(unsigned int width, unsigned int height) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = UIBase::Resize(width, height)) {
		return error.get();
	}
	if(inner_ui) {
		const unsigned int inner_width = width - left_up->GetWidth() - right_up->GetWidth();
		const unsigned int inner_height = height - left_up->GetHeight() - left_down->GetHeight();
		if(error = inner_ui->Resize(inner_width, inner_height)) {
			return error.get();
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBox::Resize(void) {
	return UIBase::Resize();
}

boost::optional<boost::shared_ptr<Error> > UIBox::SetInnerUI(boost::shared_ptr<UIBase> ui) {
	inner_ui = ui;
	return inner_ui->SetOwnerWindow(owner);
}

boost::shared_ptr<UIBase> UIBox::GetInnerUI(void) {
	return inner_ui;
}

boost::optional<boost::shared_ptr<Error> > UIBox::Draw(unsigned int abs_x, unsigned int abs_y) {
	boost::optional<boost::shared_ptr<Error> > error;

	const unsigned int bottom_x = abs_x + width - right_up->GetWidth();
	const unsigned int bottom_y = abs_y + height - left_down->GetHeight();
	if(error = left_up->Draw(			abs_x,		abs_y)) {
		return error.get();
	}
	if(error = left_down->Draw(			abs_x,		bottom_y)) {
		return error.get();
	}
	if(error = right_up->Draw(			bottom_x,	abs_y)) {
		return error.get();
	}
	if(error = right_down->Draw(		bottom_x,	bottom_y)) {
		return error.get();
	}
	if(width > left_up->GetWidth() + right_up->GetWidth()) {
		const unsigned int line_x = abs_x + left_up->GetWidth();
		const unsigned int line_len = width - left_up->GetWidth() - right_up->GetWidth();
		const unsigned int line_thick = left_up->GetHeight();
		if(error = up_line->DrawEx(		line_x,	abs_y,		line_len,	line_thick)) {
			return error.get();
		}
		if(error = down_line->DrawEx(	line_x,	bottom_y,	line_len,	line_thick)) {
			return error.get();
		}
	}
	if(height > left_up->GetHeight() + left_down->GetHeight()) {
		const unsigned int line_y = abs_y + left_up->GetHeight();
		const unsigned int line_len = height - left_up->GetHeight() - left_down->GetHeight();
		const unsigned int line_thick = left_up->GetWidth();
		if(error = left_line->DrawEx(	abs_x,		line_y,	line_thick,	line_len)) {
			return error.get();
		}
		if(error = right_line->DrawEx(	bottom_x,	line_y,	line_thick,	line_len)) {
			return error.get();
		}
	}
	if(width > left_up->GetWidth() + right_up->GetWidth() && height > left_up->GetHeight() + left_down->GetHeight()) {
		const unsigned int blank_x = abs_x + left_up->GetWidth();
		const unsigned int blank_y = abs_y + left_up->GetHeight();
		const unsigned int blank_width = width - left_up->GetWidth() - right_up->GetWidth();
		const unsigned int blank_height = height - left_up->GetHeight() - left_down->GetHeight();
		if(error = blank->DrawEx(		blank_x,	blank_y,	blank_width,	blank_height)) {
			return error.get();
		}
	}

	if(inner_ui) {
		if(error = inner_ui->Draw()) {
			return error.get();
		}
	}
	return boost::none;
}

utility::opt_error<unsigned int>::type UIBox::CalcWidth() {
	unsigned int result = left_up->GetWidth()+right_up->GetWidth();
	if(inner_ui) {
		utility::opt_error<unsigned int>::type width_opt = inner_ui->CalcWidth();
		if(width_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(width_opt);
		}
		result += boost::get<unsigned int>(width_opt);
	}
	return result;
}

utility::opt_error<unsigned int>::type UIBox::CalcHeight() {
	unsigned int result = left_up->GetHeight()+left_down->GetHeight();
	if(inner_ui) {
		utility::opt_error<unsigned int>::type height_opt = inner_ui->CalcHeight();
		if(height_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(height_opt);
		}
		result += boost::get<unsigned int>(height_opt);
	}
	return result;
}

} // uis

} // wten
