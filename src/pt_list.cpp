#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace boost::assign;

namespace {

boost::shared_ptr<PTList> instance;

} // anonymous

PTList::PTList(const std::vector<boost::shared_ptr<PTData> >& list) :
	list(list)
{
}

PTList::~PTList() {
}

//static
boost::shared_ptr<PTList> PTList::GetCurrentInstance(void) {
	if(!instance) {
		std::vector<boost::shared_ptr<PTData> > list;
		// TODO セーブデータ読み込み
		instance.reset(new PTList(list));
	}
	return instance;
}

std::vector<boost::shared_ptr<PTData> > PTList::GetList(void) {
	return list;
}

std::vector<boost::shared_ptr<PTData> >::iterator PTList::Begin(void) {
	return list.begin();
}

std::vector<boost::shared_ptr<PTData> >::iterator PTList::End(void) {
	return list.end();
}

std::vector<boost::shared_ptr<const PTData> > PTList::GetList(void) const {
	std::vector<boost::shared_ptr<const PTData> > result;
	boost::copy(list, std::back_inserter(result));
	return result;
}

std::vector<boost::shared_ptr<PTData> >::const_iterator PTList::Begin(void) const {
	return list.begin();
}

std::vector<boost::shared_ptr<PTData> >::const_iterator PTList::End(void) const {
	return list.end();
}

boost::optional<boost::shared_ptr<Error> > PTList::AddPT(boost::shared_ptr<PTData> pt) {
	list.push_back(pt);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > PTList::RemovePT(boost::shared_ptr<PTData> pt) {
	std::vector<boost::shared_ptr<PTData> >::iterator it = std::find(list.begin(), list.end(), pt);
	if(it == list.end()) {
		return CREATE_ERROR(ERROR_CODE_PT_NOT_FOUND);
	}
	list.erase(it);
	return boost::none;
}

} // wten
