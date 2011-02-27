
namespace wten {

namespace windows {

class CampStatusWindow : public CampBaseWindow {
public:
	CampStatusWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::string> default_frame_filename);
	~CampStatusWindow();
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
protected:
	const boost::shared_ptr<uis::UICharStatus> char_status_ui;
};

} // windows

} // wten
