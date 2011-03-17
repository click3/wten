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
		::DrawString(80,380,L"いざ、一攫千金に沸く城郭都市へ",0xFFFFFFFF);
		::DrawString(85,400,L"天龍の塔への挑戦ははじまった",0xFFFFFFFF);
	}
	if(frame_counter == 300) {
		::DrawString(265,90,L"それは、青天を貫く天空への旅",0xFFFFFFFF);
		::DrawString(235,110,L"神に迫らんとするバベルを極めん道のり",0xFFFFFFFF);
	}
	if(frame_counter == 600) {
		::DrawString(325,300,L"その意味すら知らぬまま",0xFFFFFFFF);
		::DrawString(295,320,L"君達はジークフロントへ向かう",0xFFFFFFFF);
	}
	if(frame_counter == 900) {
		::DrawString(30,40,L"待ちいたるは龍すら届かぬ空の果て",0xFFFFFFFF);
		::DrawString(45,60,L"天空の杯に堕ちた神なりし物",0xFFFFFFFF);
	}
	if(frame_counter == 1200) {
		::DrawString(170,400,L"計り知れざる苦難を打ち破り",0xFFFFFFFF);
		::DrawString(175,420,L"我が夢を叶えんとするため",0xFFFFFFFF);
	}
	if(frame_counter >= 1750 && frame_counter <= 2005) {
		::SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(frame_counter - 1750));
		::DrawString(184,232,L"波乱に満ちた冒険が幕を開ける……",0xFFFFFFFF);
	}
	if(frame_counter >= 2005) {
		::SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(2260 - frame_counter));
		::DrawString(184,232,L"波乱に満ちた冒険が幕を開ける……",0xFFFFFFFF);
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
