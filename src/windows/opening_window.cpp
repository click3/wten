#include "stdafx.h"

namespace wten { namespace windows {

OpeningWindow::OpeningWindow() :
	back_buffer(::MakeGraph(640, 480)), frame_counter(0)
{
}

OpeningWindow::~OpeningWindow() {
	::DeleteGraph(back_buffer);
	::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type OpeningWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event);
	if(event->GetEventType() == EVENT_TYPE_KEY) {
		boost::shared_ptr<events::KeyEvent> key = boost::static_pointer_cast<events::KeyEvent>(event);
		if(key->GetAction() == events::KeyEvent::KEY_PRESS) {
			switch(key->GetKey()) {
				case events::KeyEvent::KEY_A:
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
	if((frame_counter%4) == 0 || frame_counter > 1550) {
		::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 254);
	} else {
		::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	if(frame_counter < 1750) {
		::DrawGraph(0,0,back_buffer,TRUE);
	}
	if(frame_counter == 0) {
		::DrawString(80,380,L"�����A�ꝺ����ɕ�����s�s�s��",0xFFFFFFFF);
		::DrawString(85,400,L"�V���̓��ւ̒���͂͂��܂���",0xFFFFFFFF);
	}
	if(frame_counter == 300) {
		::DrawString(265,90,L"����́A�V���т��V��ւ̗�",0xFFFFFFFF);
		::DrawString(235,110,L"�_�ɔ����Ƃ���o�x�����ɂ߂񓹂̂�",0xFFFFFFFF);
	}
	if(frame_counter == 600) {
		::DrawString(325,300,L"���̈Ӗ�����m��ʂ܂�",0xFFFFFFFF);
		::DrawString(295,320,L"�N�B�̓W�[�N�t�����g�֌�����",0xFFFFFFFF);
	}
	if(frame_counter == 900) {
		::DrawString(30,40,L"�҂�������͗�����͂��ʋ�̉ʂ�",0xFFFFFFFF);
		::DrawString(45,60,L"�V��̔t�ɑ����_�Ȃ肵��",0xFFFFFFFF);
	}
	if(frame_counter == 1200) {
		::DrawString(170,400,L"�v��m�ꂴ�����ł��j��",0xFFFFFFFF);
		::DrawString(175,420,L"�䂪����������Ƃ��邽��",0xFFFFFFFF);
	}
	if(frame_counter >= 1750 && frame_counter <= 2005) {
		::SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(frame_counter - 1750));
		::DrawString(184,232,L"�g���ɖ������`���������J����c�c",0xFFFFFFFF);
	}
	if(frame_counter >= 2005) {
		::SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(2260 - frame_counter));
		::DrawString(184,232,L"�g���ɖ������`���������J����c�c",0xFFFFFFFF);
	}
	if(frame_counter < 1750) {
		::GetDrawScreenGraph(0,0,640,480,back_buffer);
	}
	if(frame_counter == 2266) {
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
