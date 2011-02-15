#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

UIBox::UIBox(const boost::shared_ptr<std::string>& filename) {
	BOOST_ASSERT(filename);
	BOOST_ASSERT(!filename->empty());

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
	OPT_ERROR(UIBase::SetOwnerWindow(window));
	if(inner_ui) {
		OPT_ERROR(inner_ui->SetOwnerWindow(window));
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBox::Move(void) {
	return UIBase::Move();
}

boost::optional<boost::shared_ptr<Error> > UIBox::Move(unsigned int x, unsigned int y) {
	OPT_ERROR(UIBase::Move(x, y));
	if(inner_ui) {
		const unsigned int inner_x = x + left_up->GetWidth();
		const unsigned int inner_y = y + left_up->GetHeight();
		OPT_ERROR(inner_ui->Move(inner_x, inner_y));
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBox::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(UIBase::Resize(width, height));
	if(inner_ui) {
		const unsigned int inner_width = width - left_up->GetWidth() - right_up->GetWidth();
		const unsigned int inner_height = height - left_up->GetHeight() - left_down->GetHeight();
		OPT_ERROR(inner_ui->Resize(inner_width, inner_height));
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBox::Resize(void) {
	return UIBase::Resize();
}

boost::optional<boost::shared_ptr<Error> > UIBox::SetInnerUI(boost::shared_ptr<UIBase> ui) {
	inner_ui = ui;
	if(owner.lock()) {
		return inner_ui->SetOwnerWindow(owner);
	}
	return boost::none;
}

boost::shared_ptr<UIBase> UIBox::GetInnerUI(void) {
	return inner_ui;
}

boost::optional<boost::shared_ptr<Error> > UIBox::Draw(unsigned int abs_x, unsigned int abs_y) {

	const unsigned int bottom_x = abs_x + width - right_up->GetWidth();
	const unsigned int bottom_y = abs_y + height - left_down->GetHeight();
	OPT_ERROR(left_up->Draw(			abs_x,		abs_y));
	OPT_ERROR(left_down->Draw(			abs_x,		bottom_y));
	OPT_ERROR(right_up->Draw(			bottom_x,	abs_y));
	OPT_ERROR(right_down->Draw(		bottom_x,	bottom_y));

	if(width > left_up->GetWidth() + right_up->GetWidth()) {
		const unsigned int line_x = abs_x + left_up->GetWidth();
		const unsigned int line_len = width - left_up->GetWidth() - right_up->GetWidth();
		const unsigned int line_thick = left_up->GetHeight();
		OPT_ERROR(up_line->DrawEx(		line_x,	abs_y,		line_len,	line_thick));
		OPT_ERROR(down_line->DrawEx(	line_x,	bottom_y,	line_len,	line_thick));
	}

	if(height > left_up->GetHeight() + left_down->GetHeight()) {
		const unsigned int line_y = abs_y + left_up->GetHeight();
		const unsigned int line_len = height - left_up->GetHeight() - left_down->GetHeight();
		const unsigned int line_thick = left_up->GetWidth();
		OPT_ERROR(left_line->DrawEx(	abs_x,		line_y,	line_thick,	line_len));
		OPT_ERROR(right_line->DrawEx(	bottom_x,	line_y,	line_thick,	line_len));
	}

	if(width > left_up->GetWidth() + right_up->GetWidth() && height > left_up->GetHeight() + left_down->GetHeight()) {
		const unsigned int blank_x = abs_x + left_up->GetWidth();
		const unsigned int blank_y = abs_y + left_up->GetHeight();
		const unsigned int blank_width = width - left_up->GetWidth() - right_up->GetWidth();
		const unsigned int blank_height = height - left_up->GetHeight() - left_down->GetHeight();
		OPT_ERROR(blank->DrawEx(		blank_x,	blank_y,	blank_width,	blank_height));
	}

	if(inner_ui) {
		OPT_ERROR(inner_ui->Draw());
	}
	return boost::none;
}

utility::opt_error<unsigned int>::type UIBox::CalcWidth() {
	unsigned int result = left_up->GetWidth()+right_up->GetWidth();
	if(inner_ui) {
		unsigned int width;
		OPT_UINT(width, inner_ui->CalcWidth());
		result += width;
	}
	return result;
}

utility::opt_error<unsigned int>::type UIBox::CalcHeight() {
	unsigned int result = left_up->GetHeight()+left_down->GetHeight();
	if(inner_ui) {
		unsigned int height;
		OPT_UINT(height, inner_ui->CalcHeight());
		result += height;
	}
	return result;
}

} // uis

} // wten
