
namespace wten {

namespace utility {

template <typename T>
struct opt_error {
	typedef boost::variant<boost::shared_ptr<Error>, T> type;
};

#define CREATE_ERROR(code) utility::CreateError(code, __FILE__, __LINE__)
boost::shared_ptr<Error> CreateError(ERROR_CODE code, const std::string filename, unsigned int fileline);


#define SPRINTF_IMPL_IMPL(proc, buffer, fmt, ...)	::proc(buffer, sizeof(buffer) / sizeof(*buffer), fmt, __VA_ARGS__)
#define STRLEN_IMPL(proc, buffer)				::proc(buffer, sizeof(buffer) / sizeof(*buffer))
#define SPRINTF_IMPL(proc, len_proc, buffer, fmt, ...)						\
do {													\
	const int length = SPRINTF_IMPL_IMPL(proc, buffer, fmt, __VA_ARGS__);			\
	BOOST_ASSERT(length != -1);									\
	BOOST_ASSERT(static_cast<unsigned int>(length) == STRLEN_IMPL(len_proc, buffer));	\
} while(false)
#define SPRINTF(buffer, fmt, ...)		SPRINTF_IMPL(sprintf_s, strnlen, buffer, fmt, __VA_ARGS__)
#define WSPRINTF(buffer, fmt, ...)		SPRINTF_IMPL(swprintf_s, wcsnlen, buffer, fmt, __VA_ARGS__)
#define STRLEN(buffer)			STRLEN_IMPL(strnlen, buffer)
#define WSTRLEN(buffer)			STRLEN_IMPL(wcsnlen, buffer)


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
boost::optional<boost::shared_ptr<Error> > FileRead(const std::string &path, std::vector<char> *data);
boost::optional<boost::shared_ptr<Error> > SJISFileRead(const std::string &path, std::vector<wchar_t> *result);
boost::optional<boost::shared_ptr<Error> > UTF8FileRead(const std::string &path, std::vector<wchar_t> *result);
boost::shared_ptr<const std::string> StrV2Ptr(const std::vector<char> &str);
boost::shared_ptr<const std::string> Str2Ptr(const std::string &str);
boost::shared_ptr<const std::string> Char2Ptr(const char* str);

} // utility

} // wten
