#include "stdafx.h"

namespace wten { namespace events {

ItemBuyEvent::ItemBuyEvent(boost::shared_ptr<const ItemInfo> item_info) :
	EventBase(EVENT_TYPE_ITEM_BUY), item_info(item_info)
{
	BOOST_ASSERT(item_info);
}

ItemBuyEvent::~ItemBuyEvent() {
}

boost::shared_ptr<const ItemInfo> ItemBuyEvent::GetItemInfo(void) const {
	return item_info;
}

} // events

} // wten
