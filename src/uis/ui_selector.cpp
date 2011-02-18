#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

namespace {

struct MaxFindByUIStringWidth {
	bool operator ()(const boost::shared_ptr<UIString>& left, const boost::shared_ptr<UIString>& right) {
		opt_error<unsigned int>::type left_opt = left->CalcWidth();
		BOOST_ASSERT(left_opt.which() == 1);
		opt_error<unsigned int>::type right_opt = right->CalcWidth();
		BOOST_ASSERT(right_opt.which() == 1);

		return boost::get<unsigned int>(left_opt) < boost::get<unsigned int>(right_opt);
	}
};

std::vector<boost::shared_ptr<UIString> > CreateSelectList(const std::vector<boost::shared_ptr<const std::string> >& texts) {
	std::vector<boost::shared_ptr<UIString> > result;
	BOOST_FOREACH(boost::shared_ptr<const std::string> text, texts) {
		BOOST_ASSERT(text);
		BOOST_ASSERT(!text->empty());
		boost::shared_ptr<UIString> row(new UIString(text));
		BOOST_ASSERT(row);
		result.push_back(row);
	}
	return result;
}


} // anonymous

UISelector::UISelector(const std::vector<boost::shared_ptr<const std::string> >& texts, boost::shared_ptr<const std::string> arrow_filename) :
	UIBase(), select_list(CreateSelectList(texts)), arrow(new UIImage(arrow_filename)), index(0)
{
	BOOST_ASSERT(select_list.size() == texts.size());
	BOOST_ASSERT(arrow_filename);
	BOOST_ASSERT(!arrow_filename->empty());
	BOOST_ASSERT(arrow);
}

UISelector::~UISelector() {
}

boost::optional<boost::shared_ptr<Error> > UISelector::Select(boost::shared_ptr<const std::string> text) {
	unsigned int index = 0;
	BOOST_FOREACH(boost::shared_ptr<UIString> select, select_list) {
		if(*select->GetText() == *text) {
			this->index = index;
			return boost::none;
		}
	}
	return CREATE_ERROR(ERROR_CODE_SELECTOR_TEXT_NOT_FOUND);
}

boost::optional<boost::shared_ptr<Error> > UISelector::Select(unsigned int index) {
	if(index >= select_list.size()) {
		return CREATE_ERROR(ERROR_CODE_SELECTOR_OUTSIDE_RANGE);
	}
	this->index = index;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UISelector::Select(MOVE_FOCUS move_mode) {
	if(move_mode == MOVE_FOCUS_UP) {
		if(index == 0) {
			index = select_list.size() - 1;
		} else {
			index--;
		}
	} else if(move_mode == MOVE_FOCUS_DOWN) {
		index++;
		if(index == select_list.size()) {
			index = 0;
		}
	} else {
		BOOST_ASSERT(false);
	}
	return boost::none;
}

utility::opt_error<unsigned int>::type UISelector::GetIndex() const {
	if(select_list.empty()) {
		return CREATE_ERROR(ERROR_CODE_SELECTOR_EMPTY);
	}
	return index;
}

utility::opt_error<boost::shared_ptr<const std::string> >::type UISelector::GetText() const {
	if(select_list.empty()) {
		return CREATE_ERROR(ERROR_CODE_SELECTOR_EMPTY);
	}
	BOOST_ASSERT(index < select_list.size());
	return select_list[index]->GetText();
}

boost::optional<boost::shared_ptr<Error> > UISelector::SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window) {
	BOOST_ASSERT(arrow);
	OPT_ERROR(arrow->SetOwnerWindow(window));

	BOOST_FOREACH(boost::shared_ptr<UIString> select, select_list) {
		BOOST_ASSERT(select);
		OPT_ERROR(select->SetOwnerWindow(window));
	}

	return UIBase::SetOwnerWindow(window);
}

boost::optional<boost::shared_ptr<Error> > UISelector::Move(void) {
	return UIBase::Move();
}

boost::optional<boost::shared_ptr<Error> > UISelector::Move(unsigned int x, unsigned int y) {
	OPT_ERROR(UIBase::Move(x, y));
	return UIBase::Resize();
}

boost::optional<boost::shared_ptr<Error> > UISelector::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(UIBase::Resize(width, height));

	unsigned int this_width;
	OPT_UINT(this_width, CalcWidth());
	BOOST_ASSERT(width >= this_width);

	unsigned int this_height;
	OPT_UINT(this_height, CalcHeight());
	BOOST_ASSERT(height >= this_height);

	BOOST_ASSERT(arrow);
	unsigned int arrow_width;
	OPT_UINT(arrow_width, arrow->CalcWidth());

	unsigned int arrow_height;
	OPT_UINT(arrow_height, arrow->CalcHeight());

	unsigned int arrow_x;
	unsigned int text_x;
	if(width == this_width) {
		arrow_x = 0;
		text_x = arrow_width;
	} else {
		arrow_x = (width - this_width) / 2;
		text_x = arrow_width + arrow_x;
	}

	unsigned blank_y;
	if(height == this_height) {
		blank_y = 0;
	} else {
		blank_y = (height - this_height) / 2;
	}
	unsigned int i = 0;
	unsigned int current_y = blank_y;
	BOOST_FOREACH(boost::shared_ptr<UIString> select, select_list) {
		unsigned int select_height;
		OPT_UINT(select_height, select->CalcHeight());

		const unsigned int text_y = current_y + (arrow_height > select_height ? (arrow_height - select_height) / 2 : 0);
		OPT_ERROR(select->Move(this->x + text_x, this->y + text_y));

		if(i == index) {
			const unsigned int arrow_y = current_y + (select_height > arrow_height ? (select_height - arrow_height) / 2 : 0);
			OPT_ERROR(arrow->Move(this->x + arrow_x, this->y + arrow_y));
		}
		current_y += std::max(select_height, arrow_height);
		i++;
	}

	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UISelector::Resize(void) {
	return UIBase::Resize();
}

boost::optional<boost::shared_ptr<Error> > UISelector::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UISelector::Draw(unsigned int abs_x, unsigned int abs_y) {
	BOOST_ASSERT(arrow);
	OPT_ERROR(arrow->Draw());

	BOOST_FOREACH(boost::shared_ptr<UIString> select, select_list) {
		BOOST_ASSERT(select);
		OPT_ERROR(select->Draw());
	}

	return boost::none;
}

opt_error<unsigned int>::type UISelector::CalcWidth() const {
	unsigned int result;

	unsigned int arrow_width;
	OPT_UINT(arrow_width, arrow->CalcWidth());
	result = arrow_width;

	std::vector<boost::shared_ptr<UIString> >::const_iterator it = std::max_element(select_list.begin(), select_list.end(), MaxFindByUIStringWidth());
	BOOST_ASSERT(it != select_list.end());
	boost::shared_ptr<UIString> max_select = *it;
	BOOST_ASSERT(max_select);

	unsigned int width;
	OPT_UINT(width, max_select->CalcWidth());
	result += width;

	return result;
}

opt_error<unsigned int>::type UISelector::CalcHeight() const {
	unsigned int arrow_height;
	OPT_UINT(arrow_height, arrow->CalcHeight());

	unsigned int result = 0;
	BOOST_FOREACH(boost::shared_ptr<UIString> select, select_list) {
		BOOST_ASSERT(select);
		unsigned int height;
		OPT_UINT(height, select->CalcHeight());
		result += std::max(height, arrow_height);
	}

	return result;
}

unsigned int UISelector::GetCount() const {
	return select_list.size();
}

} // uis

} // wten
