#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

namespace {

unsigned int GetUIWidth(boost::shared_ptr<UIBase> ui) {
	opt_error<unsigned int>::type width_opt = ui->CalcWidth();
	BOOST_ASSERT(width_opt.which() == 1);
	opt_error<boost::tuple<unsigned int, unsigned int> >::type size_opt = ui->GetSize();
	BOOST_ASSERT(size_opt.which() == 1);
	return std::max(boost::get<unsigned int>(width_opt), boost::get<boost::tuple<unsigned int, unsigned int> >(size_opt).get<0>());
}

unsigned int GetUIHeight(boost::shared_ptr<UIBase> ui) {
	opt_error<unsigned int>::type height_opt = ui->CalcHeight();
	BOOST_ASSERT(height_opt.which() == 1);
	opt_error<boost::tuple<unsigned int, unsigned int> >::type size_opt = ui->GetSize();
	BOOST_ASSERT(size_opt.which() == 1);
	return std::max(boost::get<unsigned int>(height_opt), boost::get<boost::tuple<unsigned int, unsigned int> >(size_opt).get<1>());
}

struct MaxFindByUIWidth {
	bool operator ()(boost::shared_ptr<UIBase> left, boost::shared_ptr<UIBase> right) {
		return GetUIWidth(left) < GetUIWidth(right);
	}
};

struct MaxFindByUIHeight {
	bool operator ()(boost::shared_ptr<UIBase> left, boost::shared_ptr<UIBase> right) {
		return GetUIHeight(left) < GetUIHeight(right);
	}
};

boost::shared_ptr<UIString> CreatePagerLabel(unsigned int size) {
	wchar_t text[256];
	WSPRINTF(text, L"%s/%s", 1, size);
	boost::shared_ptr<UIString> result(new UIString(text));
	result->Resize(150, 0);
	return result;
}

boost::shared_ptr<UIImage> CreateUIImage(boost::shared_ptr<const Graph> graph, bool turn) {
	boost::shared_ptr<UIImage> result(new UIImage(graph));
	result->SetTurn(turn);
	return result;
}

boost::shared_ptr<UIImage> CreateUIImage(boost::shared_ptr<const std::wstring> path, bool turn) {
	boost::shared_ptr<Graph> graph(new Graph(path));
	return CreateUIImage(graph, turn);
}

} // anonymous

UIPager::UIPager(const std::vector<boost::shared_ptr<uis::UIBase> > &page_list, boost::shared_ptr<const Graph> arrow_enable, boost::shared_ptr<Graph> arrow_disble) :
	page_list(page_list),
	pager_label(CreatePagerLabel(page_list.size())),
	next_arrow_enable(CreateUIImage(arrow_enable, false)),
	next_arrow_disable(CreateUIImage(arrow_disble, false)),
	prev_arrow_enable(CreateUIImage(arrow_enable, true)),
	prev_arrow_disable(CreateUIImage(arrow_disble, true)),
	page_index(0)
{
	BOOST_ASSERT(page_list.size() > 0);
	BOOST_ASSERT(pager_label);
	BOOST_ASSERT(next_arrow_enable);
	BOOST_ASSERT(next_arrow_disable);
	BOOST_ASSERT(next_arrow_enable);
	BOOST_ASSERT(next_arrow_disable);
}

UIPager::UIPager(const std::vector<boost::shared_ptr<uis::UIBase> > &page_list, boost::shared_ptr<const std::wstring> arrow_enable_path, boost::shared_ptr<const std::wstring> arrow_disable_path) :
	page_list(page_list),
	pager_label(CreatePagerLabel(page_list.size())),
	next_arrow_enable(CreateUIImage(arrow_enable_path, false)),
	next_arrow_disable(CreateUIImage(arrow_disable_path, false)),
	prev_arrow_enable(CreateUIImage(next_arrow_enable->GetImage(), true)),
	prev_arrow_disable(CreateUIImage(next_arrow_disable->GetImage(), true)),
	page_index(0)
{
	BOOST_ASSERT(page_list.size() > 0);
	BOOST_ASSERT(pager_label);
	BOOST_ASSERT(next_arrow_enable);
	BOOST_ASSERT(next_arrow_disable);
	BOOST_ASSERT(next_arrow_enable);
	BOOST_ASSERT(next_arrow_disable);
}

UIPager::~UIPager() {
}

boost::optional<boost::shared_ptr<Error> > UIPager::SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window) {
	OPT_ERROR(UIBase::SetOwnerWindow(window));
	BOOST_FOREACH(boost::shared_ptr<UIBase> page, page_list) {
		BOOST_ASSERT(page);
		OPT_ERROR(page->SetOwnerWindow(window));
	}
	OPT_ERROR(pager_label->SetOwnerWindow(window));
	OPT_ERROR(next_arrow_enable->SetOwnerWindow(window));
	OPT_ERROR(next_arrow_disable->SetOwnerWindow(window));
	OPT_ERROR(prev_arrow_enable->SetOwnerWindow(window));
	OPT_ERROR(prev_arrow_disable->SetOwnerWindow(window));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIPager::ClearOwnerWindow(void) {
	OPT_ERROR(UIBase::ClearOwnerWindow());
	BOOST_FOREACH(boost::shared_ptr<UIBase> page, page_list) {
		BOOST_ASSERT(page);
		OPT_ERROR(page->ClearOwnerWindow());
	}
	OPT_ERROR(pager_label->ClearOwnerWindow());
	OPT_ERROR(next_arrow_enable->ClearOwnerWindow());
	OPT_ERROR(next_arrow_disable->ClearOwnerWindow());
	OPT_ERROR(prev_arrow_enable->ClearOwnerWindow());
	OPT_ERROR(prev_arrow_disable->ClearOwnerWindow());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIPager::Select(MOVE_TYPE move_type) {
	switch(move_type) {
		case MOVE_TYPE_PREV:
			BOOST_ASSERT(page_index > 0);
			page_index--;
			break;
		case MOVE_TYPE_NEXT:
			BOOST_ASSERT(page_index < page_list.size() - 1);
			page_index++;
			break;
	}
	return boost::none;
}

unsigned int UIPager::GetIndex(void) const {
	return page_index;
}

boost::shared_ptr<uis::UIBase> UIPager::GetPage(void) const {
	BOOST_ASSERT(page_index < page_list.size());
	return page_list[page_index];
}

boost::optional<boost::shared_ptr<Error> > UIPager::Move(void) {
	return UIBase::Move();
}

boost::optional<boost::shared_ptr<Error> > UIPager::Move(unsigned int x, unsigned int y) {
	OPT_ERROR(UIBase::Move(x, y));
	return Resize();
}

boost::optional<boost::shared_ptr<Error> > UIPager::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(UIBase::Resize(width, height));

	unsigned int min_width;
	unsigned int min_height;
	OPT_UINT(min_width, CalcWidth());
	OPT_UINT(min_height, CalcHeight());
	BOOST_ASSERT(width >= min_width);
	BOOST_ASSERT(height >= min_height);

	unsigned int page_width;
	unsigned int page_height;
	OPT_UINT(page_width, CalcPageWidth());
	OPT_UINT(page_height, CalcPageHeight());
	
	const unsigned int page_x = (width - page_width) / 2;
	const unsigned int page_y = (height - page_height) / 2;
	OPT_ERROR(page_list[page_index]->Move(page_x, page_y));

	const unsigned int pager_height = min_height - page_height;
	next_arrow_enable->SetVisible(false);
	next_arrow_disable->SetVisible(false);
	prev_arrow_enable->SetVisible(false);
	prev_arrow_disable->SetVisible(false);

	boost::shared_ptr<UIImage> left_arrow = (page_index == 0 ? prev_arrow_disable : prev_arrow_enable);
	const unsigned int left_arrow_height = GetUIHeight(left_arrow);
	const unsigned int left_arrow_x = (width - min_width) / 2;
	const unsigned int left_arrow_y  = height - (height - min_height) / 2 - left_arrow_height + (pager_height - left_arrow_height) / 2;
	OPT_ERROR(left_arrow->Move(left_arrow_x, left_arrow_y));
	left_arrow->SetVisible(true);

	boost::shared_ptr<UIImage> right_arrow = (page_index == page_list.size() - 1 ? next_arrow_disable : next_arrow_enable);
	const unsigned int right_arrow_height = GetUIHeight(right_arrow);
	const unsigned int right_arrow_width = GetUIWidth(right_arrow);
	const unsigned int right_arrow_x = width - (width - min_width) / 2 - right_arrow_width;
	const unsigned int right_arrow_y  = height - (height - min_height) / 2 - right_arrow_height + (pager_height - right_arrow_height) / 2;
	OPT_ERROR(right_arrow->Move(right_arrow_x, right_arrow_y));
	right_arrow->SetVisible(true);

	const unsigned int label_height = GetUIHeight(pager_label);
	const unsigned int label_width = GetUIWidth(pager_label);
	const unsigned int label_x = (width - label_width) / 2;
	const unsigned int label_y = height - (height - min_height) / 2 - label_height + (pager_height - label_height) / 2;
	OPT_ERROR(pager_label->Move(label_x, label_y));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIPager::Resize(void) {
	return UIBase::Resize();
}

boost::optional<boost::shared_ptr<Error> > UIPager::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIPager::Draw(unsigned int, unsigned int) {
	BOOST_FOREACH(boost::shared_ptr<UIBase> page, page_list) {
		BOOST_ASSERT(page);
		OPT_ERROR(page->Draw());
	}
	OPT_ERROR(pager_label->Draw());
	OPT_ERROR(next_arrow_enable->Draw());
	OPT_ERROR(next_arrow_disable->Draw());
	OPT_ERROR(prev_arrow_enable->Draw());
	OPT_ERROR(prev_arrow_disable->Draw());
	return boost::none;
}

utility::opt_error<unsigned int>::type UIPager::CalcPageWidth() const {
	std::vector<boost::shared_ptr<UIBase> >::const_iterator it = std::max_element(page_list.begin(), page_list.end(), MaxFindByUIWidth());
	return GetUIWidth(*it);
}

utility::opt_error<unsigned int>::type UIPager::CalcPageHeight() const {
	std::vector<boost::shared_ptr<UIBase> >::const_iterator it = std::max_element(page_list.begin(), page_list.end(), MaxFindByUIHeight());
	return GetUIHeight(*it);
}

utility::opt_error<unsigned int>::type UIPager::CalcWidth() const {
	unsigned int page_width;
	OPT_UINT(page_width, CalcPageWidth());
	const unsigned int arrow_width = std::max(GetUIWidth(next_arrow_enable), GetUIWidth(next_arrow_disable));
	const unsigned int label_width = GetUIWidth(pager_label);
	return std::max(page_width, arrow_width * 2 + label_width);
}

utility::opt_error<unsigned int>::type UIPager::CalcHeight() const {
	unsigned int page_height;
	OPT_UINT(page_height, CalcPageHeight());
	const unsigned int pager_height = std::max(GetUIHeight(pager_label), std::max(GetUIHeight(next_arrow_enable), GetUIHeight(next_arrow_disable)));
	return page_height + pager_height;
}

unsigned int UIPager::GetPageCount(void) const {
	return page_list.size();
}

} // uis

} // wten
