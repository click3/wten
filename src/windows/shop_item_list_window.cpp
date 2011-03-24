#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;
using namespace boost::assign;

namespace {

std::vector<boost::tuple<boost::shared_ptr<uis::UIBase>, boost::shared_ptr<void> > > CreateShopItemList(void) {
	boost::shared_ptr<const ItemInfoList> item_info_list = ItemInfoList::GetCurrentInstance();
	BOOST_ASSERT(item_info_list);
	std::vector<boost::tuple<boost::shared_ptr<uis::UIBase>, boost::shared_ptr<void> > > result;
	BOOST_FOREACH(boost::shared_ptr<const ItemInfo> item_info, item_info_list->GetList()) {
		// TODO ‚¿‚á‚ñ‚Æ‚µ‚½UI
		boost::shared_ptr<uis::UIBase> ui(new uis::UIString(item_info->GetName()));
		boost::shared_ptr<void> data = boost::const_pointer_cast<ItemInfo>(item_info);
		result.push_back(boost::make_tuple(ui, data));
	}
	return result;
}

} // anonymous

void ShopItemListWindow::Initialize(void) {
	PageSelectWindow::SetSelectClose(false);
	boost::optional<boost::shared_ptr<Error> > error = SetCancelData(boost::shared_ptr<void>());
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

ShopItemListWindow::ShopItemListWindow(boost::shared_ptr<const std::wstring> default_frame_filename, unsigned int shop_page_size) :
	PageSelectWindow(CreateShopItemList(), shop_page_size, default_frame_filename), select_close(true)
{
	Initialize();
}

ShopItemListWindow::ShopItemListWindow(boost::shared_ptr<const Graph> default_frame_graph, unsigned int shop_page_size) :
	PageSelectWindow(CreateShopItemList(), shop_page_size, default_frame_graph), select_close(true)
{
	Initialize();
}

ShopItemListWindow::~ShopItemListWindow(void) {
}

bool ShopItemListWindow::IsSelectClose(void) const {
	return select_close;
}

void ShopItemListWindow::SetSelectClose(bool flag) {
	select_close = flag;
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type ShopItemListWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event);
	if(event->GetEventType() == EVENT_TYPE_ON_SELECT) {
		const boost::shared_ptr<events::OnSelectEvent> on_select_event = boost::static_pointer_cast<events::OnSelectEvent>(event);
		const boost::shared_ptr<void> user_data = on_select_event->GetUserData();
		if(!user_data) {
			OPT_ERROR(OnItemBuyCancelEvent());
			return boost::none;
		}
		const boost::shared_ptr<const ItemInfo> item_info = boost::static_pointer_cast<const ItemInfo>(user_data);
		OPT_ERROR(OnItemBuyEvent(item_info));
		return boost::none;
	}
	return PageSelectWindow::NotifyEvent(event);
}

boost::optional<boost::shared_ptr<Error> > ShopItemListWindow::OnItemBuyEvent(boost::shared_ptr<const ItemInfo> item_info) {
	boost::shared_ptr<Event> event(new events::ItemBuyEvent(item_info));
	if(select_close) {
		OPT_ERROR(RemoveThisWindow());
	}
	EventNotify::Send(event);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > ShopItemListWindow::OnItemBuyCancelEvent(void) {
	boost::shared_ptr<Event> event(new events::ItemBuyCancelEvent());
	if(select_close) {
		OPT_ERROR(RemoveThisWindow());
	}
	EventNotify::Send(event);
	return boost::none;
}

} // windows

} // wten