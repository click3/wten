#include "stdafx.h"

namespace wten { namespace errors {

ErrorNormal::ErrorNormal(ERROR_CODE error_code, const std::string& filename, unsigned int fileline) :
	code(error_code), filename(filename), fileline(fileline)
{
}

const wchar_t* ErrorNormal::ToString(void) {
	static wchar_t result[2048];
	switch(code) {
#define ADD_ERROR(name, message)	\
	case ERROR_CODE_##name:	\
		::wsprintfW(result, L"%S\ncode=%S\nfilename: %S(%d)\n", message, #name, filename.c_str(), fileline);\
		break;
	ADD_ERROR(UNKNOWN,			"�s���ȃG���[���������܂����B");
	ADD_ERROR(INTERNAL_ERROR,		"�����G���[���������܂����B");
	ADD_ERROR(DXLIB_INTERNAL_ERROR,	"DxLib�����G���[���������܂����B");
	ADD_ERROR(OUTSIDE_RANGE,		"�͈͊O�`��G���[���������܂����B");
	ADD_ERROR(SELECTOR_TEXT_NOT_FOUND,	"�Ώۂ̃e�L�X�g�����݂��܂���ł���");
	ADD_ERROR(SELECTOR_OUTSIDE_RANGE,	"�I�����͈̔͊O��I�����܂����B");
	ADD_ERROR(SELECTOR_EMPTY,		"�I������0�ł��B");
#undef ADD_ERROR
	default:
		::wsprintfW(result, L"�s���ȃG���[���������܂���\ncode=%d\nfilename: %S(%d)\n", code, filename.c_str(), fileline);
		break;
	}
	return result;
}

ERROR_CODE ErrorNormal::GetErrorCode(void) {
	return code;
}

void ErrorNormal::Abort(void) {
	::wprintf(L"Error: %s\n", ToString());
}

} // errors

} // wten
