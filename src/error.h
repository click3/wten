
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

	//Action�֌W
	ERROR_CODE_MP_SHORTAGE,			/**< MP������Ȃ������B */

	//Item�֌W
	ERROR_CODE_ITEM_BROKEN,			/**< ��ꂽ�A�C�e���ł��B */
	ERROR_CODE_ITEM_EQUIPED,			/**< �������ꂽ�A�C�e���ł��B */
	ERROR_CODE_ITEM_NONE_EQUIPED,		/**< ��������Ă��Ȃ��A�C�e���ł��B */
	ERROR_CODE_ITEM_CURSE,			/**< ���ꂽ�A�C�e���ł��B */
	ERROR_CODE_ITEM_CERTAIN,			/**< �Ӓ�ς݃A�C�e���ł��B */
	ERROR_CODE_ITEM_NONE_CURSE,			/**< ����Ă��Ȃ��A�C�e���ł��B */
	ERROR_CODE_ITEM_DISPEL_FAILURE,		/**< ����Ɏ��s�����B */
	ERROR_CODE_ITEM_COUNT_OVER,			/**< �������E���I�[�o�[�B */
	ERROR_CODE_ITEM_NOT_FOUND,			/**< �w��A�C�e����������܂���ł����B */

	//charcter�֌W
	ERROR_CODE_CHAR_LOST,			/**< �L���������X�g���܂����B */
};

class Error {
public:
	virtual ~Error() { }
	virtual const wchar_t* ToString(void) const = 0;
	virtual ERROR_CODE GetErrorCode(void) const = 0;
	virtual void Abort(void) = 0;
};

} // wten
