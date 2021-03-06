
namespace wten {

namespace windows {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class OpeningWindow : public WindowBase {
public:
	OpeningWindow(boost::shared_ptr<const std::wstring> default_frame_filename);
	OpeningWindow(boost::shared_ptr<const Graph> default_frame_graph);
	~OpeningWindow();
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
private:
	boost::optional<boost::shared_ptr<Error> > OnOK(void);

	unsigned int frame_counter;
};
#pragma warning(pop)

} // windows

} // wten
