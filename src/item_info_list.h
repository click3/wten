
namespace wten {
	
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class ItemInfoList : boost::noncopyable {
private:
	ItemInfoList(const std::vector<boost::shared_ptr<const ItemInfo> >& list);
public:
	~ItemInfoList();
	static boost::shared_ptr<ItemInfoList> GetCurrentInstance(void);
	std::vector<boost::shared_ptr<const ItemInfo> > GetList(void) const;
	std::vector<boost::shared_ptr<const ItemInfo> >::const_iterator Begin(void) const;
	std::vector<boost::shared_ptr<const ItemInfo> >::const_iterator End(void) const;
protected:
	const std::vector<boost::shared_ptr<const ItemInfo> > list;
};
#pragma warning(pop)

} // wten
