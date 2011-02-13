
namespace wten {

class windows::WindowBase;

class UI : boost::noncopyable {
public:
	virtual ~UI() { };
	virtual boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<windows::WindowBase> window);
	virtual boost::optional<boost::tuple<unsigned int, unsigned int> > GetPoint(void);
	virtual boost::optional<boost::tuple<unsigned int, unsigned int> > GetAbsolutePoint(void);
	virtual boost::optional<boost::tuple<unsigned int, unsigned int> > GetSize(void);
	virtual boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	virtual boost::optional<boost::shared_ptr<Error> > AbsoluteMove(unsigned int x, unsigned int y);
	virtual boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	virtual boost::optional<boost::shared_ptr<Error> > Draw(void);
};

} // wten
