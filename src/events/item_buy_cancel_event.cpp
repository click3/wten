#include "stdafx.h"

namespace wten { namespace events {

ItemBuyCancelEvent::ItemBuyCancelEvent() :
	EventBase(EVENT_TYPE_ITEM_BUY_CANCEL)
{
}

ItemBuyCancelEvent::~ItemBuyCancelEvent() {
}

} // events

} // wten
