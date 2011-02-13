
namespace wten {

namespace windows {

class WindowBase : public Window {
private:
	WindowBase();
public:
	static boost::shared_ptr<WindowBase> CreateWindowBase();
	~WindowBase();
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetPoint(void);
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetSize(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);

	boost::optional<boost::shared_ptr<Error> > AddUI(boost::shared_ptr<UI> ui);
	utility::opt_error<bool>::type RemoveUI(boost::shared_ptr<UI> ui);
private:
	std::vector<boost::shared_ptr<UI> > ui_stack;
	boost::weak_ptr<WindowBase> this_ptr;
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
};

} // windows

} // wten