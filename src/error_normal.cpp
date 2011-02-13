#include "stdafx.h"

namespace wten { namespace errors {

ErrorNormal::ErrorNormal(ERROR_CODE error_code) :
	code(error_code)
{
}

const wchar_t* ErrorNormal::ToString(void) {
	switch(code) {
#define ADD_ERROR(name, message) case ERROR_CODE_##name: return L##message L"\ncode = " L#name
	ADD_ERROR(UNKNOWN,			"不明なエラーが発生しました。");
	ADD_ERROR(INTERNAL_ERROR,		"内部エラーが発生しました。");
	ADD_ERROR(DXLIB_INTERNAL_ERROR,	"DxLib内部エラーが発生しました。");
#undef ADD_ERROR
	}
	static wchar_t result[2048];
	::wsprintfW(result, L"不明なエラーが発生しました\ncode = %d", code);
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
