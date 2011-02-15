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

DxLibWrapper::DxLibWrapper(bool window_mode, const std::string& title){
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
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return boost::none;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::SetWindowTitle(const std::string& title) {
	const int result = ::SetMainWindowText(title.c_str());
	if(result == -1) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return boost::none;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::SetDrawScreen(SCREEN_MODE mode) {
	const int result = ::SetDrawScreen(SCREEN_MODEToFlag(mode));
	if(result == -1) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
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
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return boost::none;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::ScreenFlip() {
	const int result = ::ScreenFlip();
	if(result == -1) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return boost::none;
}

//static
opt_error<boost::tuple<unsigned int,unsigned int> >::type DxLibWrapper::GetWindowSize() {
	int width;
	int height;
	const int result = ::GetWindowSize(&width, &height);
	if(result == -1 || width < 0 || height < 0) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return boost::make_tuple<unsigned int,unsigned int>(width, height);
}

//static
opt_error<unsigned int>::type DxLibWrapper::GetFontHeight() {
	const int result = ::GetFontSize();
	if(result == -1) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return result;
}

//static
opt_error<unsigned int>::type DxLibWrapper::GetFontWidth(const std::string& text) {
	const int result = ::GetDrawStringWidth(text.c_str(), text.length());
	if(result == -1) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return result;
}

//static
boost::optional<boost::shared_ptr<Error> > DxLibWrapper::DrawString(unsigned int x, unsigned int y, const std::string& text, Color color) {
	const int result = ::DrawString(x, y, text.c_str(), color.GetColorCode());
	if(result == -1) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return boost::none;
}


} // wten
