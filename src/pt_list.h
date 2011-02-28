
namespace wten {

class PTList : boost::noncopyable {
private:
	PTList(const std::vector<boost::shared_ptr<PTData> >& list);
public:
	~PTList();
	static boost::shared_ptr<PTList> GetCurrentInstance(void);
	std::vector<boost::shared_ptr<PTData> > GetList(void);
	std::vector<boost::shared_ptr<PTData> >::iterator Begin(void);
	std::vector<boost::shared_ptr<PTData> >::iterator End(void);
	std::vector<boost::shared_ptr<const PTData> > GetList(void) const;
	std::vector<boost::shared_ptr<PTData> >::const_iterator Begin(void) const;
	std::vector<boost::shared_ptr<PTData> >::const_iterator End(void) const;
	boost::optional<boost::shared_ptr<Error> > AddPT(boost::shared_ptr<PTData> pt);
	boost::optional<boost::shared_ptr<Error> > RemovePT(boost::shared_ptr<PTData> pt);
protected:
	std::vector<boost::shared_ptr<PTData> > list;
};

} // wten
