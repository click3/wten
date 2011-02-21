#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

namespace {

typedef boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> >  QUEUE_UI_PAIR;

boost::shared_ptr<std::string> GetACString(boost::shared_ptr<const CharData> character) {
	int ac = character->GetAC();
	char hp_str[256];
	if(ac > -10) {
		sprintf(hp_str, "%d", ac);
	} else if(ac > -20) {
		sprintf(hp_str, "LO");
	} else {
		sprintf(hp_str, "VL");
	}
	return boost::shared_ptr<std::string>(new std::string(hp_str));
}

boost::shared_ptr<std::string> GetHPString(boost::shared_ptr<const CharData> character) {
	char hp_str[256];
	sprintf(hp_str, "%d/%d", character->GetHP(), character->GetStatus()->GetHP());
	return boost::shared_ptr<std::string>(new std::string(hp_str));
}

boost::shared_ptr<std::string> GetStatusString(boost::shared_ptr<const CharData> character) {
	return character->GetCondition()->ToString();
}

boost::optional<boost::shared_ptr<Error> > ReloadTextList(boost::shared_ptr<const PTData> pt_data, const std::vector<const std::vector<boost::shared_ptr<std::string> > > *text_list) {
	if(!pt_data) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	if(text_list->size() != 6) {
		return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
	}
	BOOST_ASSERT(pt_data->GetCharacters().size() <= 6);
	unsigned int i = 0;
	BOOST_FOREACH(boost::shared_ptr<const CharData> character, pt_data->GetCharacters()) {
		BOOST_ASSERT(character);
		BOOST_ASSERT(character->GetStatus());
		if((*text_list)[i].size() != 3) {
			return CREATE_ERROR(ERROR_CODE_INVALID_PARAMETER);
		}
		boost::shared_ptr<std::string> ac = GetACString(character);
		boost::shared_ptr<std::string> hp = GetHPString(character);
		boost::shared_ptr<std::string> max_hp = GetStatusString(character);

		(*text_list)[i][0]->swap(*ac);
		(*text_list)[i][1]->swap(*hp);
		(*text_list)[i][2]->swap(*max_hp);
		i++;
	}
	return boost::none;
}

std::vector<const std::vector<boost::shared_ptr<std::string> > > CreateTextList(boost::shared_ptr<const PTData> pt_data) {
	std::vector<const std::vector<boost::shared_ptr<std::string> > > result;
	for(unsigned int i = 0; i < 6; i++) {
		std::vector<boost::shared_ptr<std::string> > row;
		row.push_back(boost::shared_ptr<std::string>(new std::string("")));
		row.push_back(boost::shared_ptr<std::string>(new std::string("")));
		row.push_back(boost::shared_ptr<std::string>(new std::string("")));
		result += row;
	}
	boost::optional<boost::shared_ptr<Error> > error = ReloadTextList(pt_data, &result);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	return result;
}

void SetColumnTitle(std::vector<std::vector<QUEUE_UI_PAIR> > *ui_list) {
	typedef boost::tuple<const char *, unsigned int> TITLE_TUPLE;
	std::vector<boost::tuple<const char *, unsigned int> > title_list;
	title_list +=	boost::make_tuple("ñºëO", 215);
 	title_list +=	boost::make_tuple("êEã∆", 125);
 	title_list +=	boost::make_tuple("AC", 40);
 	title_list +=	boost::make_tuple("HP", 110);
 	title_list +=	boost::make_tuple("STATUS", 120);

	unsigned int index = 0;
	BOOST_FOREACH(TITLE_TUPLE title, title_list) {
		boost::shared_ptr<std::string> text(new std::string(title.get<0>()));
		boost::shared_ptr<UIBase> ui(new UIString(text));
		ui->Resize(title.get<1>(), 0);
		ui_list->at(index) += make_tuple(UIQueue::ROW_POSITION_TOP, ui);
		index++;
	}
}

std::vector<std::vector<QUEUE_UI_PAIR> > CreateUIList(boost::shared_ptr<const PTData> pt_data, const std::vector<const std::vector<boost::shared_ptr<std::string> > >&text_list) {
	BOOST_ASSERT(pt_data);
	BOOST_ASSERT(pt_data->GetCharacters().size() == text_list.size());
	std::vector<std::vector<QUEUE_UI_PAIR> > ui_list(5);
	SetColumnTitle(&ui_list);
	unsigned int index = 0;
	BOOST_FOREACH(boost::shared_ptr<const CharData> character, pt_data->GetCharacters()) {
		BOOST_ASSERT(character);
		BOOST_ASSERT(character->GetStatus());
		BOOST_ASSERT(character->GetStatus()->GetJob());
		BOOST_ASSERT(text_list[index].size() == 3);
		boost::shared_ptr<UIBase> name(new UIString(character->GetStatus()->GetName()));
		boost::shared_ptr<UIBase> job(new UIString(character->GetStatus()->GetJob()->GetName()));
		boost::shared_ptr<UIBase> ac(new UIString(text_list[index][0]));
		boost::shared_ptr<UIBase> hits(new UIString(text_list[index][1]));
		boost::shared_ptr<UIBase> status(new UIString(text_list[index][2]));
		ui_list[0] += make_tuple(UIQueue::ROW_POSITION_TOP, name);
		ui_list[1] += make_tuple(UIQueue::ROW_POSITION_TOP, job);
		ui_list[2] += make_tuple(UIQueue::ROW_POSITION_TOP, ac);
		ui_list[3] += make_tuple(UIQueue::ROW_POSITION_TOP, hits);
		ui_list[4] += make_tuple(UIQueue::ROW_POSITION_TOP, status);
		index++;
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
boost::shared_ptr<UIQueue> CreateQueueUI(boost::shared_ptr<const PTData> pt_data, const std::vector<const std::vector<boost::shared_ptr<std::string> > >&text_list) {
	std::vector<std::vector<QUEUE_UI_PAIR> > ui_list = CreateUIList(pt_data, text_list);
	std::vector<UIQueue::INNER_POSITION> position_list;
	position_list += UIQueue::INNER_POSITION_LEFT, UIQueue::INNER_POSITION_CENTER, UIQueue::INNER_POSITION_RIGHT, UIQueue::INNER_POSITION_RIGHT, UIQueue::INNER_POSITION_CENTER;
	std::vector<QUEUE_UI_PAIR> row_list = CreateUIRowList(ui_list, position_list);
	return boost::shared_ptr<UIQueue>(new UIQueue(row_list));
}

} // anonymous

UIPTStatus::UIPTStatus(boost::shared_ptr<const std::string> frame_filename, boost::shared_ptr<const PTData> pt_data) :
	UIBox(boost::shared_ptr<Graph>(new Graph(frame_filename))), pt_data(pt_data), text_list(CreateTextList(pt_data)), queue_ui(CreateQueueUI(pt_data, text_list))
{
	BOOST_ASSERT(pt_data);
	boost::optional<boost::shared_ptr<Error> > error = SetInnerUI(queue_ui);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

UIPTStatus::~UIPTStatus() {
}

boost::optional<boost::shared_ptr<Error> > UIPTStatus::Draw(void) {
	return UIBox::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIPTStatus::Draw(unsigned int abs_x, unsigned int abs_y) {
	OPT_ERROR(ReloadTextList(pt_data, &text_list));
	return UIBox::Draw(abs_x, abs_y);
}

} // uis

} // wten
