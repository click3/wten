
namespace wten { namespace events {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class KeyEventChecker : public EventCheckerBase {
public:
	KeyEventChecker();
	~KeyEventChecker();
	boost::optional<boost::shared_ptr<Error> > DoCheck(void);
private:
	boost::optional<KeyEvent::ACTION> prev[KEY_MAX];
	unsigned int press_frame[KEY_MAX];
};
#pragma warning(pop)

} // events

} // wten
