#include "stdafx.h"

namespace wten { namespace utility {

namespace {

void MyFClose(FILE *fp) {
	if(fp == NULL) {
		return;
	}
	::fclose(fp);
}

boost::optional<boost::shared_ptr<Error> > FileReadW(const std::string &path, unsigned int code_page, std::vector<wchar_t> *result) {
	if(result == NULL) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	std::vector<char> multi;
	OPT_ERROR(FileRead(path, &multi));
	const int size = ::MultiByteToWideChar(code_page, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, &multi.front(), static_cast<int>(multi.size()), NULL, 0);
	if(size <= 0) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	result->resize(static_cast<unsigned int>(size));
	const int convert_size = ::MultiByteToWideChar(code_page, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, &multi.front(), static_cast<int>(multi.size()), &result->front(), static_cast<int>(result->size()));
	if(convert_size <= 0 || static_cast<unsigned int>(convert_size) != result->size()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return boost::none;
}

} // anonymous

boost::shared_ptr<Error> CreateError(ERROR_CODE code, const std::string filename, unsigned int fileline) {
	return boost::shared_ptr<Error>(new errors::ErrorNormal(code, filename, fileline));
}

unsigned int Dice(unsigned int base, unsigned int count, unsigned int bonus) {
	BOOST_ASSERT(base > 0);
	BOOST_ASSERT(count > 0);
	unsigned int result = 0;
	for(unsigned int i = 0; i < count; i++) {
		result += bonus + DxLibWrapper::GetRand(base);
	}
	return result;
}

boost::shared_ptr<FILE> MyFOpen(const std::string &path, const char *type) {
	boost::shared_ptr<FILE> result;
	FILE *fp;
	const errno_t error = ::fopen_s(&fp, path.c_str(), type);
	if(error == 0) {
		BOOST_ASSERT(fp != NULL);
		result.reset(fp, &MyFClose);
	}
	return result;
}

boost::optional<boost::shared_ptr<Error> > FileRead(const std::string &path, std::vector<char> *data) {
	if(path.empty() || data == NULL) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	boost::shared_ptr<FILE> fp = MyFOpen(path, "rb");
	if(!fp) {
		return CREATE_ERROR(ERROR_CODE_FILE_NOT_FOUND);
	}
	::fseek(fp.get(), 0, SEEK_END);
	const long size = ::ftell(fp.get());
	if(size < 0) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	::fseek(fp.get(), 0, SEEK_SET);
	data->resize(static_cast<unsigned int>(size));
	const unsigned int read_size = ::fread(&data->front(), 1, data->size(), fp.get());
	if(read_size != data->size()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > SJISFileRead(const std::string &path, std::vector<wchar_t> *result) {
	return FileReadW(path, CP_ACP, result);
}

boost::optional<boost::shared_ptr<Error> > UTF8FileRead(const std::string &path, std::vector<wchar_t> *result) {
	return FileReadW(path, CP_UTF8, result);
}

boost::shared_ptr<const std::string> StrV2Ptr(const std::vector<char> &str) {
	return boost::shared_ptr<const std::string>(new std::string(&str.front(), str.size()));
}

boost::shared_ptr<const std::string> Str2Ptr(const std::string &str) {
	return boost::shared_ptr<const std::string>(new std::string(str));
}

boost::shared_ptr<const std::string> Char2Ptr(const char* str) {
	return boost::shared_ptr<const std::string>(new std::string(str));
}

} // utility

} // wten
