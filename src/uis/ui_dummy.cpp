#include "stdafx.h"

namespace wten { namespace uis {

boost::optional<boost::shared_ptr<Error> > UIDummy::Draw(unsigned int, unsigned int) {
	return boost::none;
}

} // uis

} // wten
