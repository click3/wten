#include "stdafx.h"

namespace wten { namespace errors {

ErrorNormal::ErrorNormal(ERROR_CODE error_code) :
	code(error_code)
{
}

const wchar_t* ErrorNormal::ToString(void) {
	switch(code) {
#define ADD_ERROR(name, message) case ERROR_CODE_##name: return L##message L"\ncode = " L#name
	ADD_ERROR(UNKNOWN, "�s���ȃG���[���������܂����B");
#undef ADD_ERROR
	}
	static wchar_t result[2048];
	::wsprintfW(result, L"�s���ȃG���[���������܂���\ncode = %d", code);
	return result;
}

ERROR_CODE ErrorNormal::GetErrorCode(void) {
	return code;
}

void ErrorNormal::Abort(void) {
	
}

} // errors

} // wten
