
namespace wten {

namespace windows {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class OpeningWindow : public WindowBase {
public:
	OpeningWindow();
	~OpeningWindow();
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
private:
	boost::optional<boost::shared_ptr<Error> > OnOK(void);

	int back_buffer;
	unsigned int frame_counter;
};
#pragma warning(pop)

} // windows

} // wten
