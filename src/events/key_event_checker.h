
namespace wten { namespace events {

class KeyEventChecker : public EventCheckerBase {
public:
	KeyEventChecker();
	~KeyEventChecker();
	boost::optional<boost::shared_ptr<Error> > DoCheck(void);
private:
	KeyEvent::ACTION prev[KEY_MAX];
	unsigned int press_frame[KEY_MAX];
};

} // events

} // wten
