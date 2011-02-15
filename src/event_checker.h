
namespace wten {

class EventChecker : boost::noncopyable {
public:
	virtual ~EventChecker() { }
	virtual boost::optional<boost::shared_ptr<Error> > DoCheck(void) = 0;
};

} // wten
