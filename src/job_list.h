
namespace wten {
	
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class JobList : boost::noncopyable {
private:
	JobList(const std::vector<boost::shared_ptr<const Job> >& list);
public:
	~JobList();
	static boost::shared_ptr<JobList> GetCurrentInstance(void);
	std::vector<boost::shared_ptr<const Job> > GetList(void) const;
	std::vector<boost::shared_ptr<const Job> >::const_iterator Begin(void) const;
	std::vector<boost::shared_ptr<const Job> >::const_iterator End(void) const;
protected:
	const std::vector<boost::shared_ptr<const Job> > list;
};
#pragma warning(pop)

} // wten
