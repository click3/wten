
namespace wten {

namespace windows {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class CampStatusWindow : public CampBaseWindow {
public:
	CampStatusWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::wstring> default_frame_filename);
	~CampStatusWindow();
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
protected:
	const boost::shared_ptr<uis::UICharStatus> char_status_ui;
	boost::shared_ptr<TextWindow> text_window;
};
#pragma warning(pop)

} // windows

} // wten
