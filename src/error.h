
namespace wten { 

enum ERROR_CODE {
	ERROR_CODE_UNKNOWN,
	ERROR_CODE_DXLIB_INTERNAL_ERROR,
};

class Error {
public:
	virtual ~Error() { }
	virtual const wchar_t* ToString(void) = 0;
	virtual ERROR_CODE GetErrorCode(void) = 0;
	virtual void Abort(void) = 0;
};

} // wten
