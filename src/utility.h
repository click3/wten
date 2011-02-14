
namespace wten {

namespace utility {

template <typename T>
struct opt_error {
	typedef boost::variant<boost::shared_ptr<Error>, T> type;
};

#define CREATE_ERROR(code) CreateError(code, __FILE__, __LINE__)
boost::shared_ptr<Error> CreateError(ERROR_CODE code, const std::string filename, unsigned int fileline);

class Color {
public:
	Color(unsigned int r, unsigned int g, unsigned int b) :
		red(r), green(g), blue(b)
	{
	}

	int GetColorCode() {
		return ::GetColor(red, green, blue);
	}

	unsigned int red;
	unsigned int green;
	unsigned int blue;
};

} // utility

} // wten
