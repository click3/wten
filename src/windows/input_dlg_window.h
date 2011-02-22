
namespace wten {

namespace windows {

class InputDlgWindow : public WindowBase {
public:
	InputDlgWindow(boost::shared_ptr<const std::string> message, boost::shared_ptr<const std::string> frame_filename);
	~InputDlgWindow();
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
private:
	boost::optional<boost::shared_ptr<Error> > InputStringEvent(void);

	const boost::shared_ptr<uis::UIInputDlg> ui_input_dlg;
};

} // windows

} // wten
