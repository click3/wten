#include "stdafx.h"

namespace wten { namespace utility {

boost::shared_ptr<Error> CreateError(ERROR_CODE code, const std::string filename, unsigned int fileline) {
	return boost::shared_ptr<Error>(new errors::ErrorNormal(code, filename, fileline));
}

unsigned int dice(unsigned int base, unsigned int count, unsigned int bonus) {
	BOOST_ASSERT(base > 0);
	BOOST_ASSERT(count > 0);
	unsigned int result = 0;
	for(unsigned int i = 0; i < count; i++) {
		result += bonus + DxLibWrapper::GetRand(base);
	}
	return result;
}

} // utility

} // wten
