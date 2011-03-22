
namespace wten {

namespace windows {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class CampBaseWindow : public WindowBase {
public:
	CampBaseWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::wstring> default_frame_filename);
	CampBaseWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const Graph> default_frame_graph);
	~CampBaseWindow();
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
protected:
	void SendNextWindowEvent(boost::shared_ptr<Window> window);
	void SendPopWindowEvent(boost::shared_ptr<Window> window);
	boost::optional<boost::shared_ptr<Error> > SendNextTextWindowEvent(boost::shared_ptr<const std::wstring> text, unsigned int x = 50, unsigned int y = 50, unsigned int width = 540, unsigned int height = 380);

	const boost::shared_ptr<PTData> pt;
};
#pragma warning(pop)

} // windows

} // wten
