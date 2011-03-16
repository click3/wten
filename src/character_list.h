
namespace wten {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class CharacterList : boost::noncopyable {
private:
	CharacterList(const std::vector<boost::shared_ptr<CharData> >& list);
public:
	~CharacterList();
	static boost::shared_ptr<CharacterList> GetCurrentInstance(void);
	std::vector<boost::shared_ptr<const CharData> > GetList(void) const;
	std::vector<boost::shared_ptr<CharData> >::const_iterator Begin(void) const;
	std::vector<boost::shared_ptr<CharData> >::const_iterator End(void) const;
	std::vector<boost::shared_ptr<CharData> > GetList(void);
	std::vector<boost::shared_ptr<CharData> >::iterator Begin(void);
	std::vector<boost::shared_ptr<CharData> >::iterator End(void);
	std::vector<boost::shared_ptr<CharData> > GetFreeList(void);
	boost::optional<boost::shared_ptr<Error> > AddChar(boost::shared_ptr<CharData> char_data);
	boost::optional<boost::shared_ptr<Error> > RemoveChar(boost::shared_ptr<CharData> char_data);
protected:
	std::vector<boost::shared_ptr<CharData> > list;
};
#pragma warning(pop)

} // wten
