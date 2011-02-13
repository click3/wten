#include "stdafx.h"

namespace wten { namespace utility {

boost::shared_ptr<Error> CreateError(ERROR_CODE code) {
	return boost::shared_ptr<Error>(new errors::ErrorNormal(code));
}

} // utility

} // wten
