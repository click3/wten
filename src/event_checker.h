
namespace wten {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class EventChecker : boost::noncopyable {
public:
	virtual ~EventChecker() { }
	virtual boost::optional<boost::shared_ptr<Error> > DoCheck(void) = 0;
};
#pragma warning(pop)

} // wten
