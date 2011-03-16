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

DxLibWrapper::DxLibWrapper(bool window_mode, boost::shared_ptr<const std::string> title){
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = ChangeWindowMode(window_mode)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	if(error = SetWindowTitle(title)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	const int result = DxLib_Init();
	BOOST_ASSERT(result != -1);
}
DxLibWrapper::~DxLibWrapper() {
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
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::SetWindowTitle(boost::shared_ptr<const std::string> title) {
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
bool DxLibWrapper::ProcessMessage() {
	const int result = ::ProcessMessage();
	return (result != -1);
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::ClearDrawScreen() {
	const int result = ::ClearDrawScreen();
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::ScreenFlip() {
	const int result = ::ScreenFlip();
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

//static
opt_error<boost::tuple<unsigned int,unsigned int> >::type DxLibWrapper::GetWindowSize() {
	int width;
	int height;
	// 最小化やフルスクリーン時に0が帰るようになるため、別の方法で取得
	//const int result = ::GetWindowSize(&width, &height);
	const int result = ::GetDrawScreenSize(&width, &height);
	if(result == -1 || width < 0 || height < 0) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::make_tuple<unsigned int,unsigned int>(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

//static
opt_error<unsigned int>::type DxLibWrapper::GetFontHeight() {
	const int result = ::GetFontSize();
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return result;
}

//static
opt_error<unsigned int>::type DxLibWrapper::GetFontWidth(boost::shared_ptr<const std::string> text) {
	BOOST_ASSERT(text);
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
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::DrawString(unsigned int x, unsigned int y, boost::shared_ptr<const std::string> text, Color color) {
	BOOST_ASSERT(text);
	if(text->empty()) {
		return boost::none;
	}
	BOOST_ASSERT(x <= INT_MAX);
	BOOST_ASSERT(y <= INT_MAX);
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
opt_error<boost::shared_ptr<std::string> >::type DxLibWrapper::KeyInputString(unsigned int x, unsigned int y, unsigned int max) {
	char buffer[1024];
	BOOST_ASSERT(x <= INT_MAX);
	BOOST_ASSERT(y <= INT_MAX);
	BOOST_ASSERT(max <= INT_MAX);
	const int result = ::KeyInputString(static_cast<int>(x), static_cast<int>(y), static_cast<int>(max), buffer, FALSE);
	if(result != 1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::shared_ptr<std::string>(new std::string(buffer));
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::DrawBox(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, utility::Color color) {
	BOOST_ASSERT(x1 <= INT_MAX);
	BOOST_ASSERT(y1 <= INT_MAX);
	BOOST_ASSERT(x2 <= INT_MAX);
	BOOST_ASSERT(y2 <= INT_MAX);
	const int result = ::DrawBox(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2), color.GetColorCode(), TRUE);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

} // wten
