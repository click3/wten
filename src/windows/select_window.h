
namespace wten {

namespace windows {

class SelectWindow : public WindowBase {
private:
	SelectWindow();
public:
	static boost::shared_ptr<SelectWindow> CreateSelectWindow(const std::vector<boost::tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> > >& select_list);
	~SelectWindow();
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
private:
	boost::shared_ptr<uis::UISelector> selector;
	std::vector<boost::shared_ptr<void> > data_list;
};

} // windows

} // wten
