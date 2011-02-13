
namespace wten {

class windows::WindowBase;

class UI : boost::noncopyable {
public:
	virtual ~UI() { };
	virtual boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<windows::WindowBase> window) = 0;
	virtual utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetPoint(void) = 0;
	virtual utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetAbsolutePoint(void) = 0;
	virtual utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetSize(void) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > AbsoluteMove(unsigned int x, unsigned int y) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Draw(void) = 0;
};

} // wten
