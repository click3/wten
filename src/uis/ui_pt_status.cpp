#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

namespace {

typedef boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> >  QUEUE_UI_PAIR;

boost::shared_ptr<std::wstring> GetACString(boost::shared_ptr<const CharData> character) {
	int ac = character->GetAC();
	wchar_t hp_str[256];
	if(ac > -10) {
		WSPRINTF(hp_str, L"%d", ac);
	} else if(ac > -20) {
		WSPRINTF(hp_str, L"LO");
	} else {
		WSPRINTF(hp_str, L"VL");
	}
	return boost::shared_ptr<std::wstring>(new std::wstring(hp_str));
}

boost::shared_ptr<std::wstring> GetHPString(boost::shared_ptr<const CharData> character) {
	wchar_t hp_str[256];
	WSPRINTF(hp_str, L"%d/%d", character->GetHP(), character->GetStatus()->GetHP());
	return boost::shared_ptr<std::wstring>(new std::wstring(hp_str));
}

boost::shared_ptr<std::wstring> GetStatusString(boost::shared_ptr<const CharData> character) {
	return character->GetCondition()->ToString();
}

boost::optional<boost::shared_ptr<Error> > ReloadUIStringList(boost::shared_ptr<const PTData> pt_data, const std::vector<const std::vector<boost::shared_ptr<UIString> > > *ui_string_list) {
	if(!pt_data) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(ui_string_list->size() != PT_MEMBER_MAX) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	BOOST_ASSERT(pt_data->GetCharacters().size() <= PT_MEMBER_MAX);
	unsigned int i = 0;
	BOOST_FOREACH(boost::shared_ptr<const CharData> character, pt_data->GetCharacters()) {
		BOOST_ASSERT(character);
		BOOST_ASSERT(character->GetStatus());
		if((*ui_string_list)[i].size() != 5) {
			return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
		}
		boost::shared_ptr<std::wstring> ac = GetACString(character);
		boost::shared_ptr<std::wstring> hp = GetHPString(character);
		boost::shared_ptr<std::wstring> max_hp = GetStatusString(character);
		
		(*ui_string_list)[i][0]->SetText(character->GetStatus()->GetName());
		(*ui_string_list)[i][1]->SetText(character->GetStatus()->GetJob()->GetName());
		(*ui_string_list)[i][2]->SetText(ac);
		(*ui_string_list)[i][3]->SetText(hp);
		(*ui_string_list)[i][4]->SetText(max_hp);
		i++;
	}
	for(unsigned int i = pt_data->GetCharacters().size(); i < PT_MEMBER_MAX; i++) {
		(*ui_string_list)[i][0]->SetText(L"");
		(*ui_string_list)[i][1]->SetText(L"");
		(*ui_string_list)[i][2]->SetText(L"");
		(*ui_string_list)[i][3]->SetText(L"");
		(*ui_string_list)[i][4]->SetText(L"");
	}
	return boost::none;
}

std::vector<const std::vector<boost::shared_ptr<UIString> > > CreateUIStringList(boost::shared_ptr<const PTData> pt_data) {
	std::vector<const std::vector<boost::shared_ptr<UIString> > > result;
	for(unsigned int i = 0; i < PT_MEMBER_MAX; i++) {
		std::vector<boost::shared_ptr<uis::UIString> > row;
		row += boost::shared_ptr<UIString>(new UIString(WChar2Ptr(L"")));
		row += boost::shared_ptr<UIString>(new UIString(WChar2Ptr(L"")));
		row += boost::shared_ptr<UIString>(new UIString(WChar2Ptr(L"")));
		row += boost::shared_ptr<UIString>(new UIString(WChar2Ptr(L"")));
		row += boost::shared_ptr<UIString>(new UIString(WChar2Ptr(L"")));
		result += row;
	}
	boost::optional<boost::shared_ptr<Error> > error = ReloadUIStringList(pt_data, &result);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	return result;
}

void SetColumnTitle(std::vector<std::vector<QUEUE_UI_PAIR> > *ui_list) {
	typedef boost::tuple<const wchar_t *, unsigned int> TITLE_TUPLE;
	std::vector<boost::tuple<const wchar_t *, unsigned int> > title_list;
	title_list +=	boost::make_tuple(L"ñºëO", 215);
 	title_list +=	boost::make_tuple(L"êEã∆", 125);
 	title_list +=	boost::make_tuple(L"AC", 40);
 	title_list +=	boost::make_tuple(L"HP", 110);
 	title_list +=	boost::make_tuple(L"STATUS", 120);

	unsigned int index = 0;
	BOOST_FOREACH(TITLE_TUPLE title, title_list) {
		boost::shared_ptr<std::wstring> text(new std::wstring(title.get<0>()));
		boost::shared_ptr<UIBase> ui(new UIString(text));
		ui->Resize(title.get<1>(), 0);
		ui_list->at(index) += make_tuple(UIQueue::ROW_POSITION_TOP, ui);
		index++;
	}
}

std::vector<std::vector<QUEUE_UI_PAIR> > CreateUIList(const std::vector<const std::vector<boost::shared_ptr<UIString> > >&ui_string_list) {
	std::vector<std::vector<QUEUE_UI_PAIR> > ui_list(5);
	SetColumnTitle(&ui_list);
	BOOST_FOREACH(const std::vector<boost::shared_ptr<UIString> > row, ui_string_list) {
		ui_list[0] += make_tuple(UIQueue::ROW_POSITION_TOP, row[0]);
		ui_list[1] += make_tuple(UIQueue::ROW_POSITION_TOP, row[1]);
		ui_list[2] += make_tuple(UIQueue::ROW_POSITION_TOP, row[2]);
		ui_list[3] += make_tuple(UIQueue::ROW_POSITION_TOP, row[3]);
		ui_list[4] += make_tuple(UIQueue::ROW_POSITION_TOP, row[4]);
	}
	return ui_list;
}

std::vector<QUEUE_UI_PAIR> CreateUIRowList(const std::vector<std::vector<QUEUE_UI_PAIR> >& ui_list, std::vector<UIQueue::INNER_POSITION> position_list) {
	BOOST_ASSERT(ui_list.size() == position_list.size());
	std::vector<QUEUE_UI_PAIR> result;
	unsigned int index = 0;
	BOOST_FOREACH(std::vector<QUEUE_UI_PAIR> row, ui_list) {
		boost::shared_ptr<UIQueue> ui(new UIQueue(row, position_list[index]));
		result += make_tuple(UIQueue::COL_POSITION_LEFT, ui);
		index++;
	}
	return result;
}
boost::shared_ptr<UIQueue> CreateQueueUI(const std::vector<const std::vector<boost::shared_ptr<UIString> > >&ui_string_list) {
	std::vector<std::vector<QUEUE_UI_PAIR> > ui_list = CreateUIList(ui_string_list);
	std::vector<UIQueue::INNER_POSITION> position_list;
	position_list += UIQueue::INNER_POSITION_LEFT, UIQueue::INNER_POSITION_CENTER, UIQueue::INNER_POSITION_RIGHT, UIQueue::INNER_POSITION_RIGHT, UIQueue::INNER_POSITION_CENTER;
	std::vector<QUEUE_UI_PAIR> row_list = CreateUIRowList(ui_list, position_list);
	return boost::shared_ptr<UIQueue>(new UIQueue(row_list));
}

} // anonymous

void UIPTStatus::Initialize(void) {
	boost::optional<boost::shared_ptr<Error> > error = SetInnerUI(queue_ui);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

UIPTStatus::UIPTStatus(boost::shared_ptr<const std::wstring> frame_filename, boost::shared_ptr<const PTData> pt_data) :
	UIBox(frame_filename), pt_data(pt_data), ui_string_list(CreateUIStringList(pt_data)), queue_ui(CreateQueueUI(ui_string_list))
{
	BOOST_ASSERT(pt_data);
	Initialize();
}

UIPTStatus::UIPTStatus(boost::shared_ptr<const Graph> frame_graph, boost::shared_ptr<const PTData> pt_data) :
	UIBox(frame_graph), pt_data(pt_data), ui_string_list(CreateUIStringList(pt_data)), queue_ui(CreateQueueUI(ui_string_list))
{
	BOOST_ASSERT(pt_data);
	Initialize();
}

UIPTStatus::~UIPTStatus() {
}

boost::optional<boost::shared_ptr<Error> > UIPTStatus::Draw(void) {
	return UIBox::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIPTStatus::Draw(unsigned int abs_x, unsigned int abs_y) {
	OPT_ERROR(ReloadUIStringList(pt_data, &ui_string_list));
	return UIBox::Draw(abs_x, abs_y);
}

} // uis

} // wten
