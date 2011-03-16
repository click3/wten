
namespace wten {

class UI;
class Event;
class Error;

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class Window : boost::noncopyable {
public:
	virtual ~Window() { };
	virtual boost::optional<boost::shared_ptr<Error> > WindowInitialize(void) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > OnForeground(void) = 0;
	virtual utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetPoint(void) const = 0;
	virtual utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetSize(void) const = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height) = 0;
	virtual boost::optional<boost::shared_ptr<Error> > Draw(void) = 0;
	/**
	 * �C�x���g�ʒm
�@�@�@�@* @retval Event �㑱��Window�ɓ`�d������C�x���g
	 */
	virtual utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event) = 0;
};
#pragma warning(pop)

} // wten
