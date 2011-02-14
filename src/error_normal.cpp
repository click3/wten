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
	ADD_ERROR(UNKNOWN,			"不明なエラーが発生しました。");
	ADD_ERROR(INTERNAL_ERROR,		"内部エラーが発生しました。");
	ADD_ERROR(DXLIB_INTERNAL_ERROR,	"DxLib内部エラーが発生しました。");
	ADD_ERROR(OUTSIDE_RANGE,		"範囲外描画エラーが発生しました。");
	ADD_ERROR(SELECTOR_TEXT_NOT_FOUND,	"対象のテキストが存在しませんでした");
	ADD_ERROR(SELECTOR_OUTSIDE_RANGE,	"選択肢の範囲外を選択しました。");
	ADD_ERROR(SELECTOR_EMPTY,		"選択肢が0個です。");
#undef ADD_ERROR
	default:
		::wsprintfW(result, L"不明なエラーが発生しました\ncode=%d\nfilename: %S(%d)\n", code, filename.c_str(), fileline);
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
