
namespace wten {

namespace windows {

class ScriptWindow : public Window {
public:
	ScriptWindow();
	~ScriptWindow();
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetPoint(void);
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetSize(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
};

} // windows

} // wten
