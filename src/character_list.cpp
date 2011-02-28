#include "stdafx.h"

namespace wten {

namespace {

boost::shared_ptr<CharacterList> instance;

};

CharacterList::CharacterList(const std::vector<boost::shared_ptr<CharData> >& list) :
	list(list)
{
}

CharacterList::~CharacterList() {
}

//static
boost::shared_ptr<CharacterList> CharacterList::GetCurrentInstance(void) {
	if(!instance) {
		std::vector<boost::shared_ptr<CharData> > list;
		// TODO セーブデータ読み込み
		instance.reset(new CharacterList(list));
	}
	return instance;
}

std::vector<boost::shared_ptr<const CharData> > CharacterList::GetList(void) const {
	std::vector<boost::shared_ptr<const CharData> > result;
	boost::copy(list, std::back_inserter(result));
	return result;
}

std::vector<boost::shared_ptr<CharData> >::const_iterator CharacterList::Begin(void) const {
	return list.begin();
}

std::vector<boost::shared_ptr<CharData> >::const_iterator CharacterList::End(void) const {
	return list.end();
}

std::vector<boost::shared_ptr<CharData> > CharacterList::GetList(void) {
	return list;
}

std::vector<boost::shared_ptr<CharData> >::iterator CharacterList::Begin(void) {
	return list.begin();
}

std::vector<boost::shared_ptr<CharData> >::iterator CharacterList::End(void) {
	return list.end();
}

std::vector<boost::shared_ptr<CharData> > CharacterList::GetFreeList(void) {
	std::vector<boost::shared_ptr<CharData> > result;
	boost::copy(list, std::back_inserter(result));

	boost::shared_ptr<PTList> pt_list = PTList::GetCurrentInstance();
	BOOST_FOREACH(boost::shared_ptr<PTData> pt, pt_list->GetList()) {
		BOOST_FOREACH(boost::shared_ptr<CharData> char_data, pt->GetCharacters()) {
			result.erase(std::find(result.begin(), result.end(), char_data));
		}
	}
	return result;
}

boost::optional<boost::shared_ptr<Error> > CharacterList::AddChar(boost::shared_ptr<CharData> char_data) {
	list.push_back(char_data);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CharacterList::RemoveChar(boost::shared_ptr<CharData> char_data) {
	std::vector<boost::shared_ptr<CharData> >::iterator it = std::find(list.begin(), list.end(), char_data);
	if(it == list.end()) {
		return CREATE_ERROR(ERROR_CODE_CHAR_NOT_FOUND);
	}
	list.erase(it);
	return boost::none;
}

} // wten
