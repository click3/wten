
namespace wten { namespace errors {

class ErrorNormal : public Error {
public:
	ErrorNormal(ERROR_CODE error_code);
	const wchar_t* ToString(void);
	ERROR_CODE GetErrorCode(void);
	void Abort(void);
private:
	ERROR_CODE code;
};

} // errors

} // wten
