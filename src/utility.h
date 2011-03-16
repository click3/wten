
namespace wten {

namespace utility {

template <typename T>
struct opt_error {
	typedef boost::variant<boost::shared_ptr<Error>, T> type;
};

#define CREATE_ERROR(code) utility::CreateError(code, __FILE__, __LINE__)
boost::shared_ptr<Error> CreateError(ERROR_CODE code, const std::string filename, unsigned int fileline);


#define OPT_ERROR(in)								\
do {											\
	boost::optional<boost::shared_ptr<Error> > error = in;			\
	if(error) {									\
		return error.get();							\
	}										\
} while(false)


#define OPT_VALUE(out, in, type_name)						\
do {											\
	opt_error<type_name>::type value_opt = in;				\
	if(value_opt.which() == 0) {						\
		return boost::get<boost::shared_ptr<Error> >(value_opt);	\
	}										\
	out = boost::get<type_name>(value_opt);					\
} while(false)

#define OPT_UINT(out, in)			OPT_VALUE(out, in, unsigned int)
#define OPT_BOOL(out, in)			OPT_VALUE(out, in, bool)
#define OPT_STRING(out, in)			OPT_VALUE(out, in, std::string)
#define OPT_STRING_PTR(out, in)		OPT_VALUE(out, in, boost::shared_ptr<std::string>)
typedef boost::tuple<unsigned int, unsigned int> PAIR_UINT;
#define OPT_PAIR_UINT(out1, out2, in)	OPT_VALUE(boost::tie(out1, out2), in, PAIR_UINT)


class Color {
public:
	Color(int r, int g, int b) :
		red(r), green(g), blue(b)
	{
		BOOST_ASSERT(red >= 0);
		BOOST_ASSERT(red <= 255);
		BOOST_ASSERT(green >= 0);
		BOOST_ASSERT(green <= 255);
		BOOST_ASSERT(blue >= 0);
		BOOST_ASSERT(blue <= 255);
	}

	int GetColorCode() const {
		return static_cast<int>(::GetColor(red, green, blue));
	}

	int red;
	int green;
	int blue;
};

unsigned int Dice(unsigned int base, unsigned int count, unsigned int bonus = 0);
boost::shared_ptr<FILE> MyFOpen(const std::string &path, const char *type);

} // utility

} // wten
