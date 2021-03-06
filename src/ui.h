
namespace wten {

namespace windows {
	class WindowBase;
} // windows

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UI : boost::noncopyable {
public:
	virtual ~UI() { };
	virtual boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > ClearOwnerWindow(void) = 0;
	virtual utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetPoint(void) const = 0;
	virtual utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetAbsolutePoint(void) const = 0;
	virtual utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetSize(void) const = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > AbsoluteMove(unsigned int x, unsigned int y) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Draw(void) = 0;
};
#pragma warning(pop)

} // wten
