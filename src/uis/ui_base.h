
namespace wten {

namespace uis {

class UIBase : public UI {
public:
	UIBase();
	~UIBase();
	boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<windows::WindowBase> window);
	virtual boost::optional<boost::shared_ptr<Error> > PointAndSizeIsValid(void);
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetPoint(void);
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetAbsolutePoint(void);
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetSize(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > AbsoluteMove(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
protected:
	boost::weak_ptr<windows::WindowBase> owner;
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
};

} // uis

} // wten
