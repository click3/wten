
namespace wten { 

enum ERROR_CODE {
	ERROR_CODE_UNKNOWN,
	ERROR_CODE_INVALID_PARAMETER,
	ERROR_CODE_INTERNAL_ERROR,
	ERROR_CODE_DXLIB_INTERNAL_ERROR,

	//Window関係
	ERROR_CODE_OUTSIDE_RANGE,	/**< 座標指定などで範囲外を指定した。 */

	//UISelector関係
	ERROR_CODE_SELECTOR_TEXT_NOT_FOUND,	/**< 指定した文字列は見つからなかった。 */
	ERROR_CODE_SELECTOR_OUTSIDE_RANGE,		/**< 指定したindexは範囲外です。 */
	ERROR_CODE_SELECTOR_EMPTY,			/**< 中身が空なので実行できなかった。 */
};

class Error {
public:
	virtual ~Error() { }
	virtual const wchar_t* ToString(void) const = 0;
	virtual ERROR_CODE GetErrorCode(void) const = 0;
	virtual void Abort(void) = 0;
};

} // wten
