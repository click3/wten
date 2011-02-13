
namespace wten {

namespace utility {

template <typename T>
struct opt_error {
	typedef boost::variant<boost::shared_ptr<Error>, T> type;
};

boost::shared_ptr<Error> CreateError(ERROR_CODE code);

} // utility

} // wten
