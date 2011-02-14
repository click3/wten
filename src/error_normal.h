
namespace wten { namespace errors {

class ErrorNormal : public Error {
public:
	ErrorNormal(ERROR_CODE error_code, const std::string& filename = "Unknown", unsigned int fileline = 0);
	const wchar_t* ToString(void);
	ERROR_CODE GetErrorCode(void);
	void Abort(void);
private:
	ERROR_CODE code;
	std::string filename;
	unsigned int fileline;
};

} // errors

} // wten
