
namespace wten { 

enum ERROR_CODE {
	ERROR_CODE_UNKNOWN,
	ERROR_CODE_INTERNAL_ERROR,
	ERROR_CODE_DXLIB_INTERNAL_ERROR,

	//Window関係
	ERROR_CODE_OUTSIDE_RANGE,	/**< 座標指定などで範囲外を指定した。 */
};

class Error {
public:
	virtual ~Error() { }
	virtual const wchar_t* ToString(void) = 0;
	virtual ERROR_CODE GetErrorCode(void) = 0;
	virtual void Abort(void) = 0;
};

} // wten
