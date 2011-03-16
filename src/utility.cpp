#include "stdafx.h"

namespace wten { namespace utility {

namespace {

void MyFClose(FILE *fp) {
	if(fp == NULL) {
		return;
	}
	::fclose(fp);
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

} // utility

} // wten
