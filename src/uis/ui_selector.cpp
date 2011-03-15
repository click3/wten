#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

namespace {

unsigned int GetUIWidth(boost::shared_ptr<uis::UIBase> ui) {
	opt_error<unsigned int>::type width_opt = ui->CalcWidth();
	BOOST_ASSERT(width_opt.which() == 1);
	opt_error<boost::tuple<unsigned int, unsigned int> >::type size_opt = ui->GetSize();
	BOOST_ASSERT(size_opt.which() == 1);
	return std::max(boost::get<unsigned int>(width_opt), boost::get<boost::tuple<unsigned int, unsigned int> >(size_opt).get<0>());
}

unsigned int GetUIHeight(boost::shared_ptr<uis::UIBase> ui) {
	opt_error<unsigned int>::type height_opt = ui->CalcHeight();
	BOOST_ASSERT(height_opt.which() == 1);
	opt_error<boost::tuple<unsigned int, unsigned int> >::type size_opt = ui->GetSize();
	BOOST_ASSERT(size_opt.which() == 1);
	return std::max(boost::get<unsigned int>(height_opt), boost::get<boost::tuple<unsigned int, unsigned int> >(size_opt).get<1>());
}

struct MaxFindByUIStringWidth {
	bool operator ()(boost::shared_ptr<UIString> left, boost::shared_ptr<UIString> right) {
		return GetUIWidth(left) < GetUIWidth(right);
	}
};

struct SumByUIStringHeight {
	SumByUIStringHeight(unsigned int min) : min(min) { }
	const unsigned int min;
	unsigned int operator ()(unsigned int value, boost::shared_ptr<UIString> obj) {
		return value + std::max(min, GetUIHeight(obj));
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

UISelector::UISelector(const std::vector<boost::shared_ptr<const std::string> >& texts, unsigned int line_count, boost::shared_ptr<const std::string> arrow_filename) :
	UIBase(), select_list(CreateSelectList(texts)), arrow(new UIImage(arrow_filename)), index(0), line_count(line_count), line_size(static_cast<unsigned int>(ceil(select_list.size() / (double)line_count)))
{
	BOOST_ASSERT(select_list.size() == texts.size());
	BOOST_ASSERT(arrow_filename);
	BOOST_ASSERT(!arrow_filename->empty());
	BOOST_ASSERT(arrow);
	BOOST_ASSERT(line_count > 0);
	BOOST_ASSERT(line_count <= select_list.size());
	BOOST_ASSERT(line_size > 0);
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
	switch(move_mode) {
		case MOVE_FOCUS_UP:
			if((index % line_size) == 0) {
				index += line_size - 1;
			} else {
				index--;
			}
			break;
		case MOVE_FOCUS_DOWN:
			index++;
			if((index % line_size) == 0) {
				index -= line_size;
			}
			break;
		case MOVE_FOCUS_RIGHT:
			if(index + line_size >= select_list.size()) {
				index = index % line_size;
			} else {
				index += line_size;
			}
			break;
		case MOVE_FOCUS_LEFT:
			if(index < line_size) {
				if(((select_list.size()-1) % line_size) + 1 > index) {
					index = line_size * (line_count - 1) + index;
				} else {
					index = line_size * (line_count - 2) + index;
				}
			} else {
				index -= line_size;
			}
			break;
		default:
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

boost::optional<boost::shared_ptr<Error> > UISelector::ClearOwnerWindow(void) {
	BOOST_ASSERT(arrow);
	OPT_ERROR(arrow->ClearOwnerWindow());

	BOOST_FOREACH(boost::shared_ptr<UIString> select, select_list) {
		BOOST_ASSERT(select);
		OPT_ERROR(select->ClearOwnerWindow());
	}

	return UIBase::ClearOwnerWindow();
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
	const unsigned int arrow_width = GetUIWidth(arrow);
	const unsigned int arrow_height = GetUIHeight(arrow);

	const unsigned int blank_x = (width - this_width) / 2;
	const unsigned int blank_y = (height - this_height) / 2;

	unsigned int current_x = blank_x;
	for(unsigned int line_index = 0; line_index < line_count; line_index++) {
		unsigned int current_y = blank_y;
		for(unsigned int i = 0; i < line_size; i++) {
			const unsigned int index = line_index * line_size + i;
			const unsigned int select_height = GetUIHeight(select_list[index]);
			const unsigned int text_x = current_x + arrow_width;
			const unsigned int text_y = current_y + (arrow_height > select_height ? (arrow_height - select_height) / 2 : 0);
			OPT_ERROR(select_list[index]->Move(text_x, text_y));
			if(index == this->index) {
				const unsigned int arrow_x = current_x;
				const unsigned int arrow_y = current_y + (select_height > arrow_height ? (select_height - arrow_height) / 2 : 0);
				OPT_ERROR(arrow->Move(arrow_x, arrow_y));
			}
			current_y += std::max(select_height, arrow_height);
		}
		unsigned int line_width;
		OPT_UINT(line_width, CalcLineWidth(line_index));
		current_x += line_width;
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
	unsigned int result = 0;
	for(unsigned int i = 0; i < line_count; i++) {
		unsigned int line_width;
		OPT_UINT(line_width, CalcLineWidth(i));
		result += line_width;
	}
	return result;
}

opt_error<unsigned int>::type UISelector::CalcHeight() const {
	unsigned int result = 0;
	for(unsigned int i = 0; i < line_count; i++) {
		unsigned int line_height;
		OPT_UINT(line_height, CalcLineHeight(i));
		result = std::max(result, line_height);
	}
	return result;
}

utility::opt_error<unsigned int>::type UISelector::CalcLineWidth(unsigned int index) const {
	unsigned int result = GetUIWidth(arrow);
	std::vector<boost::shared_ptr<UIString> >::const_iterator start, end, it;
	start = select_list.begin() + line_size * index;
	if(line_size * (index + 1) >= select_list.size()) {
		end = select_list.end();
	} else {
		end = start + line_size;
	}
	it = std::max_element(start, end, MaxFindByUIStringWidth());
	result += GetUIWidth(*it);

	return result;
}

utility::opt_error<unsigned int>::type UISelector::CalcLineHeight(unsigned int index) const {
	std::vector<boost::shared_ptr<UIString> >::const_iterator start, end;
	start = select_list.begin() + line_size * index;
	if(line_size * (index + 1) >= select_list.size()) {
		end = select_list.end();
	} else {
		end = start + line_size;
	}
	return std::accumulate(start, end, 0, SumByUIStringHeight(GetUIHeight(arrow)));
}

unsigned int UISelector::GetCount() const {
	return select_list.size();
}

} // uis

} // wten
