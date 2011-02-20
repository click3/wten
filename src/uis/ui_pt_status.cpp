#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

namespace {

typedef boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> >  QUEUE_UI_PAIR;

std::vector<const std::vector<boost::shared_ptr<std::string> > > CreateTextList(boost::shared_ptr<const PTData> pt_data) {
	BOOST_ASSERT(pt_data);
	BOOST_ASSERT(pt_data->GetCharacters().size() <= 6);
	std::vector<const std::vector<boost::shared_ptr<std::string> > > result;
	BOOST_FOREACH(boost::shared_ptr<const CharData> character, pt_data->GetCharacters()) {
		BOOST_ASSERT(character);
		BOOST_ASSERT(character->GetStatus());
		std::vector<boost::shared_ptr<std::string> > row;
		boost::shared_ptr<std::string> ac(new std::string(boost::lexical_cast<std::string>(character->GetAC())));
		boost::shared_ptr<std::string> hp(new std::string(boost::lexical_cast<std::string>(character->GetHP())));
		boost::shared_ptr<std::string> max_hp(new std::string(boost::lexical_cast<std::string>(character->GetStatus()->GetHP())));
		row += ac, hp, max_hp;
		result += row;
	}
	return result;
}

void SetColumnTitle(std::vector<std::vector<QUEUE_UI_PAIR> > *ui_list) {
	typedef boost::tuple<const char *, unsigned int> TITLE_TUPLE;
	std::vector<boost::tuple<const char *, unsigned int> > title_list;
	title_list +=	boost::make_tuple("ñºëO", 100);
 	title_list +=	boost::make_tuple("êEã∆", 100);
 	title_list +=	boost::make_tuple("AC", 100);
 	title_list +=	boost::make_tuple("HP", 100);
 	title_list +=	boost::make_tuple("STATUS", 100);

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
	}
	return result;
}
boost::shared_ptr<UIQueue> CreateQueueUI(boost::shared_ptr<const PTData> pt_data, const std::vector<const std::vector<boost::shared_ptr<std::string> > >&text_list) {
	std::vector<std::vector<QUEUE_UI_PAIR> > ui_list = CreateUIList(pt_data, text_list);
	std::vector<UIQueue::INNER_POSITION> position_list;
	position_list += UIQueue::INNER_POSITION_LEFT, UIQueue::INNER_POSITION_LEFT, UIQueue::INNER_POSITION_RIGHT, UIQueue::INNER_POSITION_RIGHT, UIQueue::INNER_POSITION_RIGHT;
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

} // uis

} // wten
