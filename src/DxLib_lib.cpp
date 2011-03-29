#include "stdafx.h"

namespace wten {

using namespace utility;

namespace {

int SCREEN_MODEToFlag(DxLibWrapper::SCREEN_MODE screen_mode) {
	switch(screen_mode) {
#define ADD_MODE(mode) case DxLibWrapper::SCREEN_MODE_##mode: return DX_SCREEN_##mode
	ADD_MODE(FRONT);
	ADD_MODE(BACK);
	ADD_MODE(WORK);
	ADD_MODE(TEMPFRONT);
#undef ADD_MODE
	}
	BOOST_ASSERT(false);
	return DX_SCREEN_FRONT;
}

} // anonymous

DxLibWrapper::DxLibWrapper(bool window_mode, boost::shared_ptr<const std::wstring> title){
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = ChangeWindowMode(window_mode)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	if(error = SetWindowTitle(title)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
#ifndef _DEBUG
	::SetOutApplicationLogValidFlag(FALSE);
#endif
	::SetAlwaysRunFlag(TRUE);
	const int result = DxLib_Init();
	BOOST_ASSERT(result != -1);
}
DxLibWrapper::~DxLibWrapper(void) {
	DxLib_End();
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::ChangeWindowMode(bool window_mode) {
	const int result = ::ChangeWindowMode(window_mode ? TRUE : FALSE);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::SetWindowTitle(boost::shared_ptr<const std::wstring> title) {
	BOOST_ASSERT(title);
	BOOST_ASSERT(!title->empty());
	const int result = ::SetMainWindowText(title->c_str());
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::SetDrawScreen(SCREEN_MODE mode) {
	const int result = ::SetDrawScreen(SCREEN_MODEToFlag(mode));
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
bool DxLibWrapper::ProcessMessage(void) {
	const int result = ::ProcessMessage();
	return (result != -1);
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::ClearDrawScreen(void) {
	const int result = ::ClearDrawScreen();
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::ScreenFlip(void) {
	::ScreenFlip();
	/* SetAlwaysRunFlagÇ™TRUEÇÃéûÅAç≈è¨âªíÜÇÕ-1Ç™ãAÇÈÇΩÇﬂñ≥éãÇ∑ÇÈ
	const int result = ::ScreenFlip();
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}*/
	return boost::none;
}

//static
opt_error<boost::tuple<unsigned int,unsigned int> >::type DxLibWrapper::GetDrawScreenSize(void) {
	int width;
	int height;
	const int result = ::GetDrawScreenSize(&width, &height);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	if(width < 0) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	if(height < 0) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::make_tuple<unsigned int,unsigned int>(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

//static
opt_error<unsigned int>::type DxLibWrapper::GetFontHeight(void) {
	const int result = ::GetFontSize();
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return result;
}

//static
opt_error<unsigned int>::type DxLibWrapper::GetFontWidth(boost::shared_ptr<const std::wstring> text) {
	if(!text) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(text->empty()) {
		return 0;
	}
	const int result = ::GetDrawStringWidth(text->c_str(), static_cast<int>(text->length()));
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return result;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::DrawString(unsigned int x, unsigned int y, boost::shared_ptr<const std::wstring> text, Color color) {
	if(x > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(y > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(!text) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(text->empty()) {
		return boost::none;
	}
	const int result = ::DrawString(static_cast<int>(x), static_cast<int>(y), text->c_str(), color.GetColorCode());
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
opt_error<unsigned int>::type DxLibWrapper::GetJoypadInputState(void) {
	const int result = ::GetJoypadInputState(DX_INPUT_PAD1);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return result;
}

//static
unsigned int DxLibWrapper::GetRand(unsigned int max) {
	BOOST_ASSERT(max <= INT_MAX);
	return static_cast<unsigned int>(::GetRand(static_cast<int>(max)));
}

//static
opt_error<boost::shared_ptr<std::wstring> >::type DxLibWrapper::KeyInputString(unsigned int x, unsigned int y, unsigned int max) {
	if(x > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(y > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(max > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	wchar_t buffer[1024];
	const int result = ::KeyInputString(static_cast<int>(x), static_cast<int>(y), static_cast<int>(max), buffer, FALSE);
	if(result != 1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::shared_ptr<std::wstring>(new std::wstring(buffer));
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::DrawBox(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, utility::Color color) {
	if(x1 > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(y1 > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(x2 > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(y2 > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	const int result = ::DrawBox(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2), color.GetColorCode(), TRUE);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::InitGraph(void) {
	const int result = ::InitGraph();
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
opt_error<DxLibGraphHandle>::type DxLibWrapper::LoadGraph(boost::shared_ptr<const std::wstring> filename) {
	if(!filename) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	const int result = ::LoadGraph(filename->c_str());
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return result;
}

//static
opt_error<DxLibGraphHandle>::type DxLibWrapper::DerivationGraph(const DxLibGraphHandle handle, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	if(handle == -1) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(x > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(y > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(w > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(h > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	const int result = ::DerivationGraph(static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h), handle);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return result;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::DeleteGraph(const DxLibGraphHandle handle) {
	if(handle == -1) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	const int result = ::DeleteGraph(handle);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
opt_error<boost::tuple<unsigned int, unsigned int> >::type DxLibWrapper::GetGraphSize(const DxLibGraphHandle handle) {
	if(handle == -1) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	int x;
	int y;
	const int result = ::GetGraphSize(handle, &x, &y);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	if(x < 0) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	if(y < 0) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::make_tuple(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::DrawGraph(unsigned int x, unsigned int y, const DxLibGraphHandle handle) {
	if(x > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(y > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(handle == -1) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	const int result = ::DrawGraph(static_cast<int>(x), static_cast<int>(y), handle, TRUE);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;

}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::DrawExtendGraph(unsigned int x, unsigned int y, unsigned int w, unsigned int h, const DxLibGraphHandle handle) {
	if(x > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(y > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(x + w > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(y + h > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(handle == -1) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	const int result = ::DrawExtendGraph(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + w), static_cast<int>(y + h), handle, TRUE);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::DrawRotaGraph2(unsigned int x, unsigned int y, bool turn, double rate, double angle, unsigned int center_x, unsigned int center_y, const DxLibGraphHandle handle) {
	if(x > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(y > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(center_x > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(center_y > INT_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(handle == -1) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	const int result = ::DrawRotaGraph2(static_cast<int>(x), static_cast<int>(y), static_cast<int>(center_x), static_cast<int>(center_y), rate, angle, handle, TRUE, (turn ? TRUE : FALSE));
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

} // wten
