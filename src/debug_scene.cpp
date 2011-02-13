#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;

namespace {

class Box {
private:
	boost::shared_ptr<Graph> left_up;
	boost::shared_ptr<Graph> left_down;
	boost::shared_ptr<Graph> right_up;
	boost::shared_ptr<Graph> right_down;
	boost::shared_ptr<Graph> left_line;
	boost::shared_ptr<Graph> right_line;
	boost::shared_ptr<Graph> up_line;
	boost::shared_ptr<Graph> down_line;
	boost::shared_ptr<Graph> blank;
public:
	Box(const TCHAR* filename) {
		BOOST_ASSERT(filename != NULL);

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
	}

	bool Draw(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
		if(width < left_up->GetWidth() + right_up->GetWidth() || height < left_up->GetHeight() + left_down->GetHeight()) {
			return false;
		}

		const unsigned int bottom_x = x + width - right_up->GetWidth();
		const unsigned int bottom_y = y + height - left_down->GetHeight();
		if(!left_up->Draw(			x,		y)) {
			return false;
		}
		if(!left_down->Draw(			x,		bottom_y)) {
			return false;
		}
		if(!right_up->Draw(			bottom_x,	y)) {
			return false;
		}
		if(!right_down->Draw(		bottom_x,	bottom_y)) {
			return false;
		}
		if(width > left_up->GetWidth() + right_up->GetWidth()) {
			const unsigned int line_x = x + left_up->GetWidth();
			const unsigned int line_len = width - left_up->GetWidth() - right_up->GetWidth();
			const unsigned int line_thick = left_up->GetHeight();
			if(!up_line->DrawEx(		line_x,	y,		line_len,	line_thick)) {
				return false;
			}
			if(!down_line->DrawEx(	line_x,	bottom_y,	line_len,	line_thick)) {
				return false;
			}
		}
		if(height > left_up->GetHeight() + left_down->GetHeight()) {
			const unsigned int line_y = y + left_up->GetHeight();
			const unsigned int line_len = height - left_up->GetHeight() - left_down->GetHeight();
			const unsigned int line_thick = left_up->GetWidth();
			if(!left_line->DrawEx(	x,		line_y,	line_thick,	line_len)) {
				return false;
			}
			if(!right_line->DrawEx(	bottom_x,	line_y,	line_thick,	line_len)) {
				return false;
			}
		}
		if(width > left_up->GetWidth() + right_up->GetWidth() && height > left_up->GetHeight() + left_down->GetHeight()) {
			const unsigned int blank_x = x + left_up->GetWidth();
			const unsigned int blank_y = y + left_up->GetHeight();
			const unsigned int blank_width = width - left_up->GetWidth() - right_up->GetWidth();
			const unsigned int blank_height = height - left_up->GetHeight() - left_down->GetHeight();
			if(!blank->DrawEx(		blank_x,	blank_y,	blank_width,	blank_height)) {
				return false;
			}
		}
		return true;
	}
};

} // anonymous

DebugScene::DebugScene(void) {
}

boost::optional<boost::shared_ptr<Error> > DebugScene::DoStart(void) {
	boost::optional<boost::shared_ptr<Error> > error = SceneBase::DoStart();
	if(error) {
		return error.get();
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > DebugScene::SceneInitialize(void) {
	if(!window_manager) {
		return boost::shared_ptr<Error>(new errors::ErrorNormal(ERROR_CODE_INTERNAL_ERROR));
	}
	boost::shared_ptr<windows::WindowBase> window = windows::WindowBase::CreateWindowBase();
	if(!window) {
		return boost::shared_ptr<Error>(new errors::ErrorNormal(ERROR_CODE_INTERNAL_ERROR));
	}

	boost::optional<boost::shared_ptr<Error> > error = window_manager->PushWindow(window);
	if(error) {
		return error.get();
	}
	return boost::none;
}

} // scenes

} // wten

