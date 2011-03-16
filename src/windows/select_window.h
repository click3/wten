
namespace wten {

namespace windows {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class SelectWindow : public WindowBase {
public:
	SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input, unsigned int line_count, boost::shared_ptr<const std::string> frame_filename);
	SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input, unsigned int line_count, boost::shared_ptr<Graph> frame);
	SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& input, unsigned int line_count);
	~SelectWindow();
	bool IsSelectClose(void) const;
	void SetSelectClose(bool flag);
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	boost::optional<boost::shared_ptr<Error> > Resize();
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
private:
	boost::optional<boost::shared_ptr<Error> > OnSelect(void);
	boost::optional<boost::shared_ptr<Error> > OnSelectChange(void);

	bool select_close;
	const boost::shared_ptr<uis::UISelector> selector;
	const boost::shared_ptr<uis::UIBox> frame;
	const std::vector<boost::shared_ptr<void> > data_list;
};
#pragma warning(pop)

} // windows

} // wten
