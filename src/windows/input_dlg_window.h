
namespace wten {

namespace windows {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class InputDlgWindow : public WindowBase {
public:
	InputDlgWindow(boost::shared_ptr<const std::wstring> message, boost::shared_ptr<const std::wstring> frame_filename);
	InputDlgWindow(boost::shared_ptr<const std::wstring> message, boost::shared_ptr<const Graph> frame_graph);
	~InputDlgWindow();
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
private:
	boost::optional<boost::shared_ptr<Error> > InputStringEvent(void);

	const boost::shared_ptr<uis::UIInputDlg> ui_input_dlg;
};
#pragma warning(pop)

} // windows

} // wten
