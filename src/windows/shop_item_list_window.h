
namespace wten {

namespace windows {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class ShopItemListWindow : public PageSelectWindow {
private:
	void Initialize(void);
public:
	ShopItemListWindow(boost::shared_ptr<const std::wstring> default_frame_filename);
	ShopItemListWindow(boost::shared_ptr<const Graph> default_frame_graph);
	~ShopItemListWindow(void);
	bool IsSelectClose(void) const;
	void SetSelectClose(bool flag);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
protected:
	boost::optional<boost::shared_ptr<Error> > OnItemBuyEvent(boost::shared_ptr<const ItemInfo> item_info);
	boost::optional<boost::shared_ptr<Error> > OnItemBuyCancelEvent(void);

	bool select_close;
	unsigned char padding[3]; //unused
};
#pragma warning(pop)
#pragma pack(pop)

} // windows

} // wten