
namespace wten { namespace errors {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class ErrorNormal : public Error {
public:
	ErrorNormal(ERROR_CODE error_code, const std::string& filename = "Unknown", unsigned int fileline = 0);
	const wchar_t* ToString(void) const;
	ERROR_CODE GetErrorCode(void) const;
	void Abort(void);
private:
	const ERROR_CODE code;
	const std::string filename;
	const unsigned int fileline;
};
#pragma warning(pop)

} // errors

} // wten
