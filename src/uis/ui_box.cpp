#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

namespace {

#define RETURN_DERIVATION_GRAPH(src, x, y, w, h) 							\
{														\
	opt_error<boost::shared_ptr<Graph>>::type graph_opt = src->Derivation(x, y, w, h);\
	BOOST_ASSERT(graph_opt.which() == 1);								\
	return boost::get<boost::shared_ptr<Graph> >(graph_opt);					\
}

boost::shared_ptr<Graph> GetLeftUp(boost::shared_ptr<const Graph> src) {
	const unsigned int width = (src->GetWidth() - 1) / 2;
	const unsigned int height = (src->GetHeight() - 1) / 2;
	const unsigned int x = 0;
	const unsigned int y = 0;
	RETURN_DERIVATION_GRAPH(src, x, y, width, height);
}

boost::shared_ptr<Graph> GetLeftDown(boost::shared_ptr<const Graph> src) {
	const unsigned int width = (src->GetWidth() - 1) / 2;
	const unsigned int height = (src->GetHeight() - 1) / 2;
	const unsigned int x = 0;
	const unsigned int y = height + 1;
	RETURN_DERIVATION_GRAPH(src, x, y, width, height);
}

boost::shared_ptr<Graph> GetRightUp(boost::shared_ptr<const Graph> src) {
	const unsigned int width = (src->GetWidth() - 1) / 2;
	const unsigned int height = (src->GetHeight() - 1) / 2;
	const unsigned int x = width + 1;
	const unsigned int y = 0;
	RETURN_DERIVATION_GRAPH(src, x, y, width, height);
}

boost::shared_ptr<Graph> GetRightDown(boost::shared_ptr<const Graph> src) {
	const unsigned int width = (src->GetWidth() - 1) / 2;
	const unsigned int height = (src->GetHeight() - 1) / 2;
	const unsigned int x = width + 1;
	const unsigned int y = height + 1;
	RETURN_DERIVATION_GRAPH(src, x, y, width, height);
}

boost::shared_ptr<Graph> GetLeftLine(boost::shared_ptr<const Graph> src) {
	const unsigned int width = (src->GetWidth() - 1) / 2;
	const unsigned int height = 1;
	const unsigned int x = 0;
	const unsigned int y = (src->GetHeight() - 1) / 2;
	RETURN_DERIVATION_GRAPH(src, x, y, width, height);
}

boost::shared_ptr<Graph> GetRightLine(boost::shared_ptr<const Graph> src) {
	const unsigned int width = (src->GetWidth() - 1) / 2;
	const unsigned int height = 1;
	const unsigned int x = width + 1;
	const unsigned int y = (src->GetHeight() - 1) / 2;
	RETURN_DERIVATION_GRAPH(src, x, y, width, height);
}

boost::shared_ptr<Graph> GetTopLine(boost::shared_ptr<const Graph> src) {
	const unsigned int width = 1;
	const unsigned int height = (src->GetHeight() - 1) / 2;
	const unsigned int x = (src->GetWidth() - 1) / 2;
	const unsigned int y = 0;
	RETURN_DERIVATION_GRAPH(src, x, y, width, height);
}

boost::shared_ptr<Graph> GetBottomLine(boost::shared_ptr<const Graph> src) {
	const unsigned int width = 1;
	const unsigned int height = (src->GetHeight() - 1) / 2;
	const unsigned int x = (src->GetWidth() - 1) / 2;
	const unsigned int y = height + 1;
	RETURN_DERIVATION_GRAPH(src, x, y, width, height);
}

boost::shared_ptr<Graph> GetBlank(boost::shared_ptr<const Graph> src) {
	const unsigned int width = 1;
	const unsigned int height = 1;
	const unsigned int x = (src->GetWidth() - 1) / 2;
	const unsigned int y = (src->GetHeight() - 1) / 2;
	RETURN_DERIVATION_GRAPH(src, x, y, width, height);
}

opt_error<unsigned int>::type GetUIWidth(boost::shared_ptr<UIBase> ui) {
	unsigned int calc;
	OPT_UINT(calc, ui->CalcWidth());
	unsigned int width;
	unsigned int height;
	OPT_PAIR_UINT(width, height, ui->GetSize());
	return std::max(calc, width);
}

opt_error<unsigned int>::type GetUIHeight(boost::shared_ptr<UIBase> ui) {
	unsigned int calc;
	OPT_UINT(calc, ui->CalcHeight());
	unsigned int width;
	unsigned int height;
	OPT_PAIR_UINT(width, height, ui->GetSize());
	return std::max(calc, height);
}

} // anonymous

UIBox::UIBox(boost::shared_ptr<const Graph> src) :
	src(src),
	left_up(GetLeftUp(src)), left_down(GetLeftDown(src)), right_up(GetRightUp(src)), right_down(GetRightDown(src)),
	left_line(GetLeftLine(src)), right_line(GetRightLine(src)), top_line(GetTopLine(src)), bottom_line(GetBottomLine(src)),
	blank(GetBlank(src))
{
	BOOST_ASSERT(src);
	BOOST_ASSERT((src->GetWidth() % 2) == 1);
	BOOST_ASSERT(src->GetHeight() == src->GetHeight());
}

UIBox::UIBox(boost::shared_ptr<const std::wstring> filename) :
	src(new Graph(filename)),
	left_up(GetLeftUp(src)), left_down(GetLeftDown(src)), right_up(GetRightUp(src)), right_down(GetRightDown(src)),
	left_line(GetLeftLine(src)), right_line(GetRightLine(src)), top_line(GetTopLine(src)), bottom_line(GetBottomLine(src)),
	blank(GetBlank(src))
{
	BOOST_ASSERT(src);
	BOOST_ASSERT(filename);
	BOOST_ASSERT(!filename->empty());
	BOOST_ASSERT((src->GetWidth() % 2) == 1);
	BOOST_ASSERT(src->GetHeight() == src->GetHeight());
}


UIBox::~UIBox() {
}

boost::optional<boost::shared_ptr<Error> > UIBox::SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window) {
	OPT_ERROR(UIBase::SetOwnerWindow(window));
	if(inner_ui) {
		OPT_ERROR(inner_ui->SetOwnerWindow(window));
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIBox::ClearOwnerWindow(void) {
	OPT_ERROR(UIBase::ClearOwnerWindow());
	if(inner_ui) {
		OPT_ERROR(inner_ui->ClearOwnerWindow());
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
		BOOST_ASSERT(width >= left_up->GetWidth() - right_up->GetWidth());
		BOOST_ASSERT(height >= left_up->GetHeight() - left_down->GetHeight());
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

boost::shared_ptr<UIBase> UIBox::GetInnerUI(void) const {
	return inner_ui;
}

boost::optional<boost::shared_ptr<Error> > UIBox::Draw(void) {
	return UIBase::Draw();
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
		OPT_ERROR(top_line->DrawEx(		line_x,	abs_y,		line_len,	line_thick));
		OPT_ERROR(bottom_line->DrawEx(	line_x,	bottom_y,	line_len,	line_thick));
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

utility::opt_error<unsigned int>::type UIBox::CalcWidth() const {
	unsigned int result = left_up->GetWidth()+right_up->GetWidth();
	if(inner_ui) {
		unsigned int width;
		OPT_UINT(width, GetUIWidth(inner_ui));
		result += width;
	}
	return result;
}

utility::opt_error<unsigned int>::type UIBox::CalcHeight() const {
	unsigned int result = left_up->GetHeight()+left_down->GetHeight();
	if(inner_ui) {
		unsigned int height;
		OPT_UINT(height, GetUIHeight(inner_ui));
		result += height;
	}
	return result;
}

} // uis

} // wten
