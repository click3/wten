#include "stdafx.h"

namespace wten { namespace windows {

OpeningWindow::OpeningWindow() :
	frame_counter(0)
{
}

OpeningWindow::~OpeningWindow() {
	::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type OpeningWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event);
	if(event->GetEventType() == EVENT_TYPE_KEY) {
		boost::shared_ptr<events::KeyEvent> key = boost::static_pointer_cast<events::KeyEvent>(event);
		if(key->GetAction() == events::KeyEvent::KEY_PRESS) {
			switch(key->GetKey()) {
				case events::KeyEvent::KEY_A:
				case events::KeyEvent::KEY_B:
					OPT_ERROR(OnOK());
					return boost::none;
				default:
					break;
			}
		}
	}
	return event;
}

boost::optional<boost::shared_ptr<Error> > OpeningWindow::Draw(void) {
#define SPEED	(3)
#define FADEOUT_TEXT(start) \
	if(start <= frame_counter && frame_counter <= start + 255 * SPEED && ::SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 - (frame_counter - start) / SPEED)) != -1)

	FADEOUT_TEXT(1) {
		::DrawString(80,380,L"�����A�ꝺ����ɕ�����s�s�s��",0xFFFFFFFF);
		::DrawString(85,400,L"�V���̓��ւ̒���͂͂��܂���",0xFFFFFFFF);
		::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	FADEOUT_TEXT(256) {
		::DrawString(265,90,L"����́A�V���т��V��ւ̗�",0xFFFFFFFF);
		::DrawString(235,110,L"�_�ɔ����Ƃ���o�x�����ɂ߂񓹂̂�",0xFFFFFFFF);
		::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	FADEOUT_TEXT(512) {
		::DrawString(325,300,L"���̈Ӗ�����m��ʂ܂�",0xFFFFFFFF);
		::DrawString(295,320,L"�N�B�̓W�[�N�t�����g�֌�����",0xFFFFFFFF);
		::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
#undef SPEED
#define SPEED (2)
	FADEOUT_TEXT(768) {
		::DrawString(30,40,L"�҂�������͗�����͂��ʋ�̉ʂ�",0xFFFFFFFF);
		::DrawString(45,60,L"�V��̔t�ɑ����_�Ȃ肵��",0xFFFFFFFF);
		::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
#undef SPEED
#define SPEED (1)
	FADEOUT_TEXT(1024) {
		::DrawString(170,400,L"�v��m�ꂴ�����ł��j��",0xFFFFFFFF);
		::DrawString(175,420,L"�䂪����������Ƃ��邽��",0xFFFFFFFF);
	}
	if(frame_counter >= 1300 && frame_counter <= 1300 + 255) {
		::SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(frame_counter - 1300));
		::DrawString(184,232,L"�g���ɖ������`���������J����c�c",0xFFFFFFFF);
	}
	if(frame_counter >= 1300 + 255) {
		::SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(1300 + 255 + 255 - frame_counter));
		::DrawString(184,232,L"�g���ɖ������`���������J����c�c",0xFFFFFFFF);
	}
	if(frame_counter == 1300 + 255 + 255) {
		OPT_ERROR(OnOK());
	}
	frame_counter++;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > OpeningWindow::OnOK(void) {
	boost::shared_ptr<Event> event(new events::NextStepEvent());
	OPT_ERROR(RemoveThisWindow());
	EventNotify::Send(event);
	return boost::none;
}

} // windows

} // wten
