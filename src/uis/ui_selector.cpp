#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

namespace {

std::vector<boost::shared_ptr<UIBase> > CreateSelectList(const std::vector<boost::shared_ptr<const std::wstring> >& texts) {
	std::vector<boost::shared_ptr<UIBase> > result;
	BOOST_FOREACH(boost::shared_ptr<const std::wstring> text, texts) {
		BOOST_ASSERT(text);
		BOOST_ASSERT(!text->empty());
		boost::shared_ptr<UIBase> row(new UIString(text));
		BOOST_ASSERT(row);
		result.push_back(row);
	}
	return result;
}

} // anonymous

UISelector::UISelector(const std::vector<boost::shared_ptr<const std::wstring> >& texts) :
	UISelectorBase(CreateSelectList(texts))
{
}

UISelector::UISelector(const std::vector<boost::shared_ptr<const std::wstring> >& texts, unsigned int line_count) :
	UISelectorBase(CreateSelectList(texts), line_count)
{
}

UISelector::UISelector(const std::vector<boost::shared_ptr<const std::wstring> >& texts, unsigned int line_count, boost::shared_ptr<const std::wstring> arrow_filename) :
	UISelectorBase(CreateSelectList(texts), line_count, arrow_filename)
{
}

UISelector::~UISelector() {
}

boost::optional<boost::shared_ptr<Error> > UISelector::Select(boost::shared_ptr<const std::wstring> text) {
	unsigned int index = 0;
	BOOST_FOREACH(boost::shared_ptr<UIBase> select, select_list) {
		boost::shared_ptr<UIString> str = boost::static_pointer_cast<UIString>(select);
		if(*str->GetText() == *text) {
			this->index = index;
			return boost::none;
		}
	}
	return CREATE_ERROR(ERROR_CODE_SELECTOR_TEXT_NOT_FOUND);
}

boost::optional<boost::shared_ptr<Error> > UISelector::Select(unsigned int index) {
	return UISelectorBase::Select(index);
}

boost::optional<boost::shared_ptr<Error> > UISelector::Select(MOVE_FOCUS move_mode) {
	return UISelectorBase::Select(move_mode);
}

utility::opt_error<boost::shared_ptr<const std::wstring> >::type UISelector::GetText() const {
	BOOST_ASSERT(index < select_list.size());
	return boost::static_pointer_cast<UIString>(select_list[index])->GetText();
}

} // uis

} // wten
