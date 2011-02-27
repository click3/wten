
namespace wten {

namespace windows {

class TextWindow : public WindowBase {
public:
	TextWindow(boost::shared_ptr<const std::string> text, boost::shared_ptr<const std::string> frame_filename);
	TextWindow(boost::shared_ptr<const std::string> text, boost::shared_ptr<Graph> frame);
	TextWindow(boost::shared_ptr<const std::string> text);
	~TextWindow();
	bool IsOkClose(void) const;
	void SetOkClose(bool flag);
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
private:
	boost::optional<boost::shared_ptr<Error> > OnOK(void);

	bool ok_close;
	const boost::shared_ptr<uis::UIString> ui_string;
	const boost::shared_ptr<uis::UIBox> frame;
};

} // windows

} // wten
