#include "stdafx.h"

namespace wten {

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

DxLibWrapper::DxLibWrapper(bool window_mode){
	ChangeWindowMode(window_mode);
	const int result = DxLib_Init();
	BOOST_ASSERT(result != -1);
}
DxLibWrapper::~DxLibWrapper() {
	DxLib_End();
}


boost::optional<boost::shared_ptr<Error> > DxLibWrapper::ChangeWindowMode(bool window_mode) {
	const int result = ::ChangeWindowMode(window_mode ? TRUE : FALSE);
	if(result == -1) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > DxLibWrapper::SetDrawScreen(SCREEN_MODE mode) {
	const int result = ::SetDrawScreen(SCREEN_MODEToFlag(mode));
	if(result == -1) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return boost::none;
}

bool DxLibWrapper::ProcessMessage() {
	const int result = ::ProcessMessage();
	return (result != -1);
}

boost::optional<boost::shared_ptr<Error> > DxLibWrapper::ClearDrawScreen() {
	const int result = ::ClearDrawScreen();
	if(result == -1) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > DxLibWrapper::ScreenFlip() {
	const int result = ::ScreenFlip();
	if(result == -1) {
		return boost::shared_ptr<Error>(new errors::DxLibError);
	}
	return boost::none;
}


} // wten
