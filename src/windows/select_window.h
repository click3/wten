
namespace wten {

namespace windows {

class SelectWindow : public WindowBase {
private:
	SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input, boost::shared_ptr<Graph> frame);
	SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input);
	void InitializeUI();
public:
	static boost::shared_ptr<SelectWindow> CreateSelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input, boost::shared_ptr<const std::string> frame_filename = boost::shared_ptr<const std::string>());
	~SelectWindow();
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
private:
	boost::optional<boost::shared_ptr<Error> > OnSelect(void);

	const boost::shared_ptr<uis::UISelector> selector;
	const boost::shared_ptr<uis::UIBox> frame;
	const std::vector<boost::shared_ptr<void> > data_list;
};

} // windows

} // wten
