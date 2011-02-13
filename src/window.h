
namespace wten {

class UI;
class Event;
class Error;

class Window : boost::noncopyable {
public:
	virtual ~Window() { };
	virtual boost::optional<boost::tuple<unsigned int, unsigned int> > GetPoint(void) = 0;
	virtual boost::optional<boost::tuple<unsigned int, unsigned int> > GetSize(void) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Draw(void) = 0;
	/**
	 * �C�x���g�ʒm
�@�@�@�@* @retval Event �㑱��Window�ɓ`�d������C�x���g
	 */
	virtual utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event) = 0;
};

} // wten
