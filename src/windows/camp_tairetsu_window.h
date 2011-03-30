
namespace wten {

namespace windows {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class CampTairetsuWindow : public CampBaseWindow {
public:
	CampTairetsuWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::wstring> default_frame_filename);
	CampTairetsuWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const Graph> default_frame_graph);
	~CampTairetsuWindow();
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
};
#pragma warning(pop)

} // windows

} // wten
