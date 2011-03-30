#include "stdafx.h"

namespace wten { namespace events {

TairetsuSelectedEvent::TairetsuSelectedEvent(const std::vector<boost::shared_ptr<CharData> > &char_list) :
	EventBase(EVENT_TYPE_TAIRETSU_SELECTED), char_list(char_list)
{
}

TairetsuSelectedEvent::~TairetsuSelectedEvent() {
}

std::vector<boost::shared_ptr<CharData> > TairetsuSelectedEvent::GetCharList(void) const {
	return char_list;
}

} // events

} // wten
