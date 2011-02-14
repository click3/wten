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


} // anonymous

UISelector::UISelector(std::vector<std::string> texts, const std::string& arrow_filename) :
	UIBase()
{
	BOOST_ASSERT(!arrow_filename.empty());
	arrow.reset(new UIImage(arrow_filename));
	BOOST_ASSERT(arrow);

	BOOST_FOREACH(std::string text, texts) {
		boost::optional<boost::shared_ptr<Error> > error = AddSelect(text);
		if(error) {
			error.get()->Abort();
			BOOST_ASSERT(false);
		}
	}

	index = 0;
}

UISelector::~UISelector() {
}

boost::optional<boost::shared_ptr<Error> > UISelector::AddSelect(const std::string& text) {
	boost::shared_ptr<UIString> str(new UIString(text));
	if(!str) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	select_list.push_back(str);
	if(owner.lock()) {
		return Move();
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UISelector::Select(const std::string& text) {
	unsigned int index = 0;
	BOOST_FOREACH(boost::shared_ptr<UIString> select, select_list) {
		opt_error<std::string>::type str_opt = select->GetText();
		if(str_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(str_opt);
		}
		if(text == boost::get<std::string>(str_opt)) {
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

utility::opt_error<unsigned int>::type UISelector::GetIndex() {
	if(select_list.empty()) {
		return CREATE_ERROR(ERROR_CODE_SELECTOR_EMPTY);
	}
	return index;
}

utility::opt_error<std::string>::type UISelector::GetText() {
	if(select_list.empty()) {
		return CREATE_ERROR(ERROR_CODE_SELECTOR_EMPTY);
	}
	BOOST_ASSERT(index < select_list.size());
	opt_error<std::string>::type str_opt = select_list[index]->GetText();
	if(str_opt.which() == 0) {
		return boost::get<boost::shared_ptr<Error> >(str_opt);
	}
	return boost::get<std::string>(str_opt);
}

boost::optional<boost::shared_ptr<Error> > UISelector::SetOwnerWindow(boost::weak_ptr<windows::WindowBase> window) {
	boost::optional<boost::shared_ptr<Error> > error;

	BOOST_ASSERT(arrow);
	if(error = arrow->SetOwnerWindow(window)) {
		return error.get();
	}

	BOOST_FOREACH(boost::shared_ptr<UIString> select, select_list) {
		BOOST_ASSERT(select);
		if(error = select->SetOwnerWindow(window)) {
			return error.get();
		}
	}

	return UIBase::SetOwnerWindow(window);
}

boost::optional<boost::shared_ptr<Error> > UISelector::Move(void) {
	return UIBase::Move();
}

boost::optional<boost::shared_ptr<Error> > UISelector::Move(unsigned int x, unsigned int y) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = UIBase::Move(x, y)) {
		return error.get();
	}
	return UIBase::Resize();
}

boost::optional<boost::shared_ptr<Error> > UISelector::Resize(unsigned int width, unsigned int height) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = UIBase::Resize(width, height)) {
		return error.get();
	}

	unsigned int this_width;
	{
		opt_error<unsigned int>::type width_opt = CalcWidth();
		if(width_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(width_opt);
		}
		this_width = boost::get<unsigned int>(width_opt);
	}
	BOOST_ASSERT(width >= this_width);

	unsigned int this_height;
	{
		opt_error<unsigned int>::type height_opt = CalcHeight();
		if(height_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(height_opt);
		}
		this_height = boost::get<unsigned int>(height_opt);
	}
	BOOST_ASSERT(height >= this_height);

	BOOST_ASSERT(arrow);
	unsigned int arrow_width;
	{
		opt_error<unsigned int>::type width_opt = arrow->CalcWidth();
		if(width_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(width_opt);
		}
		arrow_width = boost::get<unsigned int>(width_opt);
	}

	unsigned int arrow_height;
	{
		opt_error<unsigned int>::type height_opt = arrow->CalcHeight();
		if(height_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(height_opt);
		}
		arrow_height = boost::get<unsigned int>(height_opt);
	}

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
		{
			opt_error<unsigned int>::type height_opt = select->CalcHeight();
			if(height_opt.which() == 0) {
				return boost::get<boost::shared_ptr<Error> >(height_opt);
			}
			select_height = boost::get<unsigned int>(height_opt);
		}

		const unsigned int text_y = current_y + (arrow_height > select_height ? (arrow_height - select_height) / 2 : 0);
		if(error = select->Move(this->x + text_x, this->y + text_y)) {
			return error.get();
		}

		if(i == index) {
			const unsigned int arrow_y = current_y + (select_height > arrow_height ? (select_height - arrow_height) / 2 : 0);
			if(error = arrow->Move(this->x + arrow_x, this->y + arrow_y)) {
				return error.get();
			}
		}
		current_y += std::max(select_height, arrow_height);
		i++;
	}

	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UISelector::Resize(void) {
	return UIBase::Resize();
}

boost::optional<boost::shared_ptr<Error> > UISelector::Draw(unsigned int abs_x, unsigned int abs_y) {
	boost::optional<boost::shared_ptr<Error> > error;

	BOOST_ASSERT(arrow);
	if(error = arrow->Draw()) {
		return error.get();
	}

	BOOST_FOREACH(boost::shared_ptr<UIString> select, select_list) {
		BOOST_ASSERT(select);
		if(error = select->Draw()) {
			return error.get();
		}
	}

	return boost::none;
}

opt_error<unsigned int>::type UISelector::CalcWidth() {
	unsigned int result;

	{
		BOOST_ASSERT(arrow);
		opt_error<unsigned int>::type arrow_width_opt = arrow->CalcWidth();
		if(arrow_width_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(arrow_width_opt);
		}
		result = boost::get<unsigned int>(arrow_width_opt);
	}

	{
		std::vector<boost::shared_ptr<UIString> >::iterator it = std::max_element(select_list.begin(), select_list.end(), MaxFindByUIStringWidth());
		BOOST_ASSERT(it != select_list.end());
		boost::shared_ptr<UIString> max_select = *it;
		BOOST_ASSERT(max_select);
		opt_error<unsigned int>::type width_opt = max_select->CalcWidth();
		if(width_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(width_opt);
		}
		result += boost::get<unsigned int>(width_opt);
	}

	return result;
}

opt_error<unsigned int>::type UISelector::CalcHeight() {
	unsigned int arrow_height;
	{
		BOOST_ASSERT(arrow);
		opt_error<unsigned int>::type arrow_height_opt = arrow->CalcHeight();
		if(arrow_height_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(arrow_height_opt);
		}
		arrow_height = boost::get<unsigned int>(arrow_height_opt);
	}

	unsigned int result = 0;
	BOOST_FOREACH(boost::shared_ptr<UIString> select, select_list) {
		BOOST_ASSERT(select);
		opt_error<unsigned int>::type height_opt = select->CalcHeight();
		if(height_opt.which() == 0) {
			return boost::get<boost::shared_ptr<Error> >(height_opt);
		}
		result += std::max(boost::get<unsigned int>(height_opt), arrow_height);
	}

	return result;
}

} // uis

} // wten
