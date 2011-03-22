
namespace wten {

namespace windows {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class CampWindow : public WindowBase {
private:
	void Initialize(void);
public:
	CampWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::wstring> default_frame_filename);
	CampWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const Graph> default_frame_graph);
	~CampWindow();
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	boost::optional<boost::shared_ptr<Error> > OnForeground(void);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
protected:
	const boost::shared_ptr<PTData> pt;
	const boost::shared_ptr<uis::UIString> money_text;
	const boost::shared_ptr<uis::UIString> play_time_text;
	boost::shared_ptr<windows::SelectWindow> select_window;
};
#pragma warning(pop)

} // windows

} // wten
