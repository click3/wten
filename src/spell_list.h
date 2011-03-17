
namespace wten {
	
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class SpellList : boost::noncopyable {
private:
	SpellList(const std::vector<boost::shared_ptr<const actions::SpellBase> >& list);
public:
	~SpellList();
	static boost::shared_ptr<SpellList> GetCurrentInstance(void);
	std::vector<boost::shared_ptr<const actions::SpellBase> > GetList(void) const;
	std::vector<boost::shared_ptr<const actions::SpellBase> >::const_iterator Begin(void) const;
	std::vector<boost::shared_ptr<const actions::SpellBase> >::const_iterator End(void) const;
protected:
	const std::vector<boost::shared_ptr<const actions::SpellBase> > list;
};
#pragma warning(pop)

} // wten
