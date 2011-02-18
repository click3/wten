
namespace wten { 

enum ERROR_CODE {
	ERROR_CODE_UNKNOWN,
	ERROR_CODE_INVALID_PARAMETER,
	ERROR_CODE_INTERNAL_ERROR,
	ERROR_CODE_DXLIB_INTERNAL_ERROR,

	//Window�֌W
	ERROR_CODE_OUTSIDE_RANGE,	/**< ���W�w��ȂǂŔ͈͊O���w�肵���B */

	//UISelector�֌W
	ERROR_CODE_SELECTOR_TEXT_NOT_FOUND,	/**< �w�肵��������͌�����Ȃ������B */
	ERROR_CODE_SELECTOR_OUTSIDE_RANGE,		/**< �w�肵��index�͔͈͊O�ł��B */
	ERROR_CODE_SELECTOR_EMPTY,			/**< ���g����Ȃ̂Ŏ��s�ł��Ȃ������B */
};

class Error {
public:
	virtual ~Error() { }
	virtual const wchar_t* ToString(void) const = 0;
	virtual ERROR_CODE GetErrorCode(void) const = 0;
	virtual void Abort(void) = 0;
};

} // wten
