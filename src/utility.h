
namespace wten {

class Error;

namespace utility {

template <typename T>
struct opt_error {
	typedef boost::variant<boost::shared_ptr<Error>, T> type;
};

} // utility

} // wten
