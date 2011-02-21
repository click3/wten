
namespace wten {

namespace windows {

class ScriptWindow : public WindowBase {
public:
	ScriptWindow();
	~ScriptWindow();
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetPoint(void) const;
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetSize(void) const;
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);

	boost::optional<boost::shared_ptr<Error> > AddEventProc(EVENT_TYPE event_type, boost::function<boost::optional<boost::shared_ptr<Error> > (boost::shared_ptr<Event>)> proc);
protected:
	std::multimap<EVENT_TYPE, boost::function<boost::optional<boost::shared_ptr<Error> > (boost::shared_ptr<Event>)> > proc_list;
};

} // windows

} // wten
