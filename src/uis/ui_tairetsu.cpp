#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

namespace {

unsigned int UiQueueColWidth() {
	boost::shared_ptr<std::wstring> str(new std::wstring(L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	opt_error<unsigned int>::type opt_width = DxLibWrapper::GetFontWidth(str);
	if(opt_width.which() == 0) {
		boost::get<boost::shared_ptr<Error> >(opt_width)->Abort();
		BOOST_ASSERT(false);
	}
	return boost::get<unsigned int>(opt_width);
}

std::vector<boost::shared_ptr<UIString> > CreateUIStringList(void) {
	std::vector<boost::shared_ptr<UIString> > result;
	for(unsigned int i = 0; i < PT_MEMBER_MAX; i++) {
		result += boost::shared_ptr<UIString>(new UIString(L""));
	}
	return result;
}

boost::shared_ptr<UIQueue> CreateUIQueue(boost::shared_ptr<const Graph> default_frame_graph, const std::vector<boost::shared_ptr<UIString> > &ui_string_list) {
	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > ui_list;
	const unsigned int str_width = UiQueueColWidth();

#define ADD_UISTRING(ui_string)							\
	do {										\
		boost::optional<boost::shared_ptr<Error> > error;		\
		if(error = ui_string->Resize(str_width, 0)) {			\
			error.get()->Abort();					\
			BOOST_ASSERT(false);						\
		}									\
		boost::shared_ptr<UIBox> ui(new UIBox(default_frame_graph));	\
		error = ui->SetInnerUI(ui_string);					\
		if(error) {								\
			error.get()->Abort();					\
			BOOST_ASSERT(false);						\
		}									\
		ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, ui);	\
	}while(false)

	boost::shared_ptr<UIString> front_label(new UIString(L"FRONT"));
	ADD_UISTRING(front_label);
	for(unsigned i = 0; i < FRONT_MEMBER_MAX; i++) {
		ADD_UISTRING(ui_string_list[i]);
	}

	boost::shared_ptr<UIString> back_label(new UIString(L"BACK"));
	ADD_UISTRING(back_label);
	for(unsigned i = 0; i < BACK_MEMBER_MAX; i++) {
		ADD_UISTRING(ui_string_list[FRONT_MEMBER_MAX + i]);
	}
#undef ADD_UISTRING
	return boost::shared_ptr<UIQueue>(new UIQueue(ui_list));
}

boost::shared_ptr<UIQueue> CreateUIQueue(boost::shared_ptr<const std::wstring> default_frame_filename, const std::vector<boost::shared_ptr<UIString> > &ui_string_list) {
	return CreateUIQueue(boost::shared_ptr<Graph>(new Graph(default_frame_filename)), ui_string_list);
}

} // anonymous

UITairetsu::UITairetsu(boost::shared_ptr<const std::wstring> frame_filename, boost::shared_ptr<const std::wstring> arrow_filename) :
	index(0), arrow(new UIImage(arrow_filename)), char_data_list(PT_MEMBER_MAX), ui_string_list(CreateUIStringList()), ui_queue(CreateUIQueue(frame_filename, ui_string_list))
{
}

UITairetsu::UITairetsu(boost::shared_ptr<const Graph> frame_graph, boost::shared_ptr<const std::wstring> arrow_filename) :
	index(0), arrow(new UIImage(arrow_filename)), char_data_list(PT_MEMBER_MAX), ui_string_list(CreateUIStringList()), ui_queue(CreateUIQueue(frame_graph, ui_string_list))
{
}

UITairetsu::~UITairetsu() {
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::Set(boost::shared_ptr<CharData> char_data) {
	const unsigned index = GetIndex();
	BOOST_ASSERT(index < PT_MEMBER_MAX);
	char_data_list[index] = char_data;
	OPT_ERROR(ResetUI());
	return boost::none;
}

boost::shared_ptr<CharData> UITairetsu::Get(void) const {
	return char_data_list[index];
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::Select(unsigned int index) {
	BOOST_ASSERT(index < PT_MEMBER_MAX);
	this->index = index;
	OPT_ERROR(ResetUI());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::Select(MOVE_FOCUS move_mode) {
	switch(move_mode) {
		case MOVE_FOCUS_UP:
			if(index == 0) {
				index = PT_MEMBER_MAX - 1;
			} else {
				index--;
			}
			break;
		case MOVE_FOCUS_DOWN:
			if(index == PT_MEMBER_MAX - 1) {
				index = 0;
			} else {
				index++;
			}
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	OPT_ERROR(ResetUI());
	return boost::none;
}

unsigned int UITairetsu::GetIndex() const {
	return index;
}

bool UITairetsu::IsArrowEnable(void) const {
	return arrow_enable;
}

void UITairetsu::SetArrowEnable(bool arrow_enable) {
	this->arrow_enable = arrow_enable;
}

std::vector<boost::shared_ptr<CharData> > UITairetsu::GetCharDataList(void) const {
	return char_data_list;
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window) {
	OPT_ERROR(UIBase::SetOwnerWindow(window));
	OPT_ERROR(arrow->SetOwnerWindow(window));
	OPT_ERROR(ui_queue->SetOwnerWindow(window));
	OPT_ERROR(ResetUI());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::ClearOwnerWindow(void) {
	OPT_ERROR(UIBase::ClearOwnerWindow());
	OPT_ERROR(arrow->ClearOwnerWindow());
	OPT_ERROR(ui_queue->ClearOwnerWindow());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::ResetUI(void) {
	for(unsigned int i = 0; i < PT_MEMBER_MAX; i++) {
		BOOST_ASSERT(i < ui_string_list.size());
		BOOST_ASSERT(ui_string_list[i]);
		BOOST_ASSERT(i < char_data_list.size());
		if(char_data_list[i]) {
			OPT_ERROR(ui_string_list[i]->SetText(char_data_list[i]->GetStatus()->GetName()));
		} else {
			OPT_ERROR(ui_string_list[i]->SetText(WChar2Ptr(L"")));
		}
	}

	BOOST_ASSERT(arrow);
	const unsigned int arrow_width = arrow->GetWidth();
	const unsigned int ui_queue_x = this->x + arrow_width;
	const unsigned int ui_queue_y = this->y;
	BOOST_ASSERT(ui_queue);
	OPT_ERROR(ui_queue->Move(ui_queue_x, ui_queue_y));

	unsigned int text_x;
	unsigned int text_y;
	OPT_PAIR_UINT(text_x, text_y, ui_string_list[index]->GetPoint());
	const unsigned int text_height = ui_string_list[index]->GetHeight();
	const unsigned int arrow_height = arrow->GetHeight();
	const unsigned int ui_arrow_x = this->x;
	const unsigned int ui_arrow_y = text_y + text_height / 2 - arrow_height / 2;
	OPT_ERROR(arrow->Move(ui_arrow_x, ui_arrow_y));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::Move(void) {
	return UIBase::Move();
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::Move(unsigned int x, unsigned int y) {
	OPT_ERROR(UIBase::Move(x, y));
	OPT_ERROR(ResetUI());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::Resize(void) {
	return UIBase::Resize();
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(UIBase::Resize(width, height));
	OPT_ERROR(ResetUI());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UITairetsu::Draw(unsigned int, unsigned int) {
	if(arrow_enable) {
		OPT_ERROR(arrow->Draw());
	}
	OPT_ERROR(ui_queue->Draw());
	return boost::none;
}

opt_error<unsigned int>::type UITairetsu::CalcWidth() const {
	const unsigned int ui_queue_width = ui_queue->GetWidth();
	const unsigned int arrow_width = arrow->GetWidth();
	return ui_queue_width + arrow_width;
}

opt_error<unsigned int>::type UITairetsu::CalcHeight() const {
	const unsigned int ui_queue_height = ui_queue->GetHeight();
	const unsigned int arrow_height = arrow->GetHeight();
	return std::max(ui_queue_height, arrow_height);
}

} // uis

} // wten
