
namespace wten {

namespace events {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class ItemBuyEvent : public EventBase {
public:
	ItemBuyEvent(boost::shared_ptr<const ItemInfo> item_info);
	~ItemBuyEvent();
	boost::shared_ptr<const ItemInfo> GetItemInfo(void) const;
private:
	const boost::shared_ptr<const ItemInfo> item_info;
};
#pragma warning(pop)
#pragma pack(pop)

} // events

} // wten
