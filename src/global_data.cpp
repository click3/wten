#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace boost::assign;

namespace {

boost::shared_ptr<GlobalData> this_ptr;

} // anonymous

GlobalData::GlobalData() :
	data(DATA_INDEX_MAX)
{
	// TODO
}

GlobalData::~GlobalData() {
	// TODO
}

//static
boost::shared_ptr<GlobalData> GlobalData::GetCurrentInstance(void) {
	if(!this_ptr) {
		this_ptr.reset(new GlobalData());
	}
	return this_ptr;
}

} // wten
