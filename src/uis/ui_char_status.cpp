#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

namespace {

enum STATUS_TEXT {
	STATUS_TEXT_NAME,
	STATUS_TEXT_LV,
	STATUS_TEXT_ALIGNMENT,
	STATUS_TEXT_JOB,
	STATUS_TEXT_EXP,
	STATUS_TEXT_TG,
	STATUS_TEXT_AC,
	STATUS_TEXT_HP,
	STATUS_TEXT_CONDITION,
	STATUS_TEXT_STR,
	STATUS_TEXT_IQ,
	STATUS_TEXT_PIE,
	STATUS_TEXT_VIT,
	STATUS_TEXT_AGI,
	STATUS_TEXT_LUK,
	STATUS_TEXT_MAGE_MP,
	STATUS_TEXT_PRIEST_MP,
	STATUS_TEXT_MAX,
};

std::vector<boost::shared_ptr<std::string> > CreateTextList(void) {
	std::vector<boost::shared_ptr<std::string> > result;
	for(unsigned int i = 0; i < STATUS_TEXT_MAX; i++) {
		result += boost::shared_ptr<std::string>(new std::string(""));
	}
	return result;
}

boost::shared_ptr<UIBase> CreateUIIdentification(
	boost::shared_ptr<const std::string> name, boost::shared_ptr<const std::string> lv,
	boost::shared_ptr<const std::string> alignment, boost::shared_ptr<const std::string> job)
{
	boost::shared_ptr<UIBase> dummy_name(new UIDummy());
	dummy_name->Resize(180,0);
	boost::shared_ptr<UIBase> dummy_lv(new UIDummy());
	dummy_lv->Resize(30,0);
	boost::shared_ptr<UIBase> name_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Name:"))));
	boost::shared_ptr<UIBase> name_ui_impl(new UIString(name));
	boost::shared_ptr<UIBase> lv_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Lv:"))));
	boost::shared_ptr<UIBase> lv_ui_impl(new UIString(lv));
	boost::shared_ptr<UIBase> alignment_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("   "))));
	boost::shared_ptr<UIBase> alignment_ui(new UIString(alignment));
	boost::shared_ptr<UIBase> job_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("-"))));
	boost::shared_ptr<UIBase> job_ui(new UIString(job));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > name_ui_list;
	name_ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, dummy_name);
	name_ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, name_ui_impl);
	boost::shared_ptr<UIBase> name_ui(new UIQueue(name_ui_list, UIQueue::INNER_POSITION_LEFT));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > lv_ui_list;
	lv_ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, dummy_lv);
	lv_ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, lv_ui_impl);
	boost::shared_ptr<UIBase> lv_ui(new UIQueue(lv_ui_list, UIQueue::INNER_POSITION_RIGHT));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > ui_list;
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_LEFT, name_label_ui);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_LEFT, name_ui);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_RIGHT, lv_label_ui);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_RIGHT, lv_ui);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_RIGHT, alignment_label_ui);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_RIGHT, alignment_ui);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_RIGHT, job_label_ui);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_RIGHT, job_ui);
	boost::shared_ptr<UIBase> result(new UIQueue(ui_list));

	return result;
}

boost::shared_ptr<UIBase> CreateUIOther(
	boost::shared_ptr<const std::string> exp, boost::shared_ptr<const std::string> tg, boost::shared_ptr<const std::string> ac,
	boost::shared_ptr<const std::string> hp, boost::shared_ptr<const std::string> condition)
{
	boost::shared_ptr<UIBase> dummy_label_left(new UIDummy());
	dummy_label_left->Resize(150, 0);
	boost::shared_ptr<UIBase> dummy_label_right(new UIDummy());
	dummy_label_right->Resize(150, 0);
	boost::shared_ptr<UIBase> dummy_center(new UIDummy());
	dummy_center->Resize(50, 0);
	boost::shared_ptr<UIBase> exp_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Exp:"))));
	boost::shared_ptr<UIBase> exp_ui(new UIString(exp));
	boost::shared_ptr<UIBase> tg_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("TowerGold:"))));
	boost::shared_ptr<UIBase> tg_ui(new UIString(tg));
	boost::shared_ptr<UIBase> hp_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("HP:"))));
	boost::shared_ptr<UIBase> hp_ui(new UIString(hp));
	boost::shared_ptr<UIBase> ac_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("AC:"))));
	boost::shared_ptr<UIBase> ac_ui(new UIString(ac));
	boost::shared_ptr<UIBase> condition_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Status:"))));
	boost::shared_ptr<UIBase> condition_ui(new UIString(condition));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > left_label_list;
	left_label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, dummy_label_left);
	left_label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, exp_label_ui);
	left_label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, tg_label_ui);
	left_label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, hp_label_ui);
	boost::shared_ptr<UIBase> left_labels(new UIQueue(left_label_list, UIQueue::INNER_POSITION_LEFT));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > left_ui_list;
	left_ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, exp_ui);
	left_ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, tg_ui);
	left_ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, hp_ui);
	boost::shared_ptr<UIBase> left_texts(new UIQueue(left_ui_list, UIQueue::INNER_POSITION_RIGHT));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > right_label_list;
	right_label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, dummy_label_right);
	right_label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, ac_label_ui);
	right_label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, condition_label_ui);
	boost::shared_ptr<UIBase> right_labels(new UIQueue(right_label_list, UIQueue::INNER_POSITION_LEFT));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > right_ui_list;
	right_ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, ac_ui);
	right_ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, condition_ui);
	boost::shared_ptr<UIBase> right_texts(new UIQueue(right_ui_list, UIQueue::INNER_POSITION_RIGHT));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > ui_list;
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_LEFT, left_labels);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_RIGHT, left_texts);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_RIGHT, dummy_center);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_RIGHT, right_labels);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_RIGHT, right_texts);
	boost::shared_ptr<UIBase> result(new UIQueue(ui_list, UIQueue::INNER_POSITION_TOP));

	return result;
}

boost::shared_ptr<UIBase> CreateUIStatus(
	boost::shared_ptr<const std::string> str, boost::shared_ptr<const std::string> iq, boost::shared_ptr<const std::string> pie,
	boost::shared_ptr<const std::string> vit, boost::shared_ptr<const std::string> agi, boost::shared_ptr<const std::string> luk,
	boost::shared_ptr<const std::string> mage_mp, boost::shared_ptr<const std::string> priest_mp)
{
	boost::shared_ptr<UIBase> str_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Str:"))));
	boost::shared_ptr<UIBase> iq_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("IQ:"))));
	boost::shared_ptr<UIBase> pie_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Pie:"))));
	boost::shared_ptr<UIBase> vit_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Vit:"))));
	boost::shared_ptr<UIBase> agi_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Agi:"))));
	boost::shared_ptr<UIBase> luk_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Luk:"))));
	boost::shared_ptr<UIBase> mage_mp_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Mage:"))));
	boost::shared_ptr<UIBase> priest_mp_label_ui(new UIString(boost::shared_ptr<std::string>(new std::string("Priest:"))));
	boost::shared_ptr<UIBase> str_ui(new UIString(str));
	boost::shared_ptr<UIBase> iq_ui(new UIString(iq));
	boost::shared_ptr<UIBase> pie_ui(new UIString(pie));
	boost::shared_ptr<UIBase> vit_ui(new UIString(vit));
	boost::shared_ptr<UIBase> agi_ui(new UIString(agi));
	boost::shared_ptr<UIBase> luk_ui(new UIString(luk));
	boost::shared_ptr<UIBase> mage_mp_ui(new UIString(mage_mp));
	boost::shared_ptr<UIBase> priest_mp_ui(new UIString(priest_mp));

	boost::shared_ptr<UIBase> dummy_label(new UIDummy());
	dummy_label->Resize(0, 20);
	boost::shared_ptr<UIBase> dummy_value(new UIDummy());
	dummy_value->Resize(0, 20);

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > label_list;
	label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, str_label_ui);
	label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, iq_label_ui);
	label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, pie_label_ui);
	label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, vit_label_ui);
	label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, agi_label_ui);
	label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, luk_label_ui);
	label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, dummy_label);
	label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, mage_mp_label_ui);
	label_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, priest_mp_label_ui);
	boost::shared_ptr<UIBase> labels(new UIQueue(label_list, UIQueue::INNER_POSITION_LEFT));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > value_list;
	value_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, str_ui);
	value_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, iq_ui);
	value_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, pie_ui);
	value_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, vit_ui);
	value_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, agi_ui);
	value_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, luk_ui);
	value_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, dummy_value);
	value_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, mage_mp_ui);
	value_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, priest_mp_ui);
	boost::shared_ptr<UIBase> values(new UIQueue(value_list, UIQueue::INNER_POSITION_RIGHT));

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > ui_list;
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_LEFT, labels);
	ui_list += boost::make_tuple(UIQueue::COL_POSITION_LEFT, values);
	boost::shared_ptr<UIBase> result(new UIQueue(ui_list));

	return result;
}


boost::shared_ptr<UIBase> CreateInnerUI(const std::vector<boost::shared_ptr<std::string> >& text_list) {
	BOOST_ASSERT(text_list.size() == STATUS_TEXT_MAX);
	boost::shared_ptr<UIBase> ui_identification = CreateUIIdentification(
		text_list[STATUS_TEXT_NAME], text_list[STATUS_TEXT_LV], text_list[STATUS_TEXT_ALIGNMENT], text_list[STATUS_TEXT_JOB]);
	boost::shared_ptr<UIBase> ui_other = CreateUIOther(
		text_list[STATUS_TEXT_EXP], text_list[STATUS_TEXT_TG], text_list[STATUS_TEXT_AC], text_list[STATUS_TEXT_HP], text_list[STATUS_TEXT_CONDITION]);
	boost::shared_ptr<UIBase> ui_status = CreateUIStatus(
		text_list[STATUS_TEXT_STR], text_list[STATUS_TEXT_IQ], text_list[STATUS_TEXT_PIE],
		text_list[STATUS_TEXT_VIT], text_list[STATUS_TEXT_AGI], text_list[STATUS_TEXT_LUK],
		text_list[STATUS_TEXT_MAGE_MP], text_list[STATUS_TEXT_PRIEST_MP]);

	boost::shared_ptr<UIBase> dummy_blank_1(new UIDummy());
	dummy_blank_1->Resize(0, 20);
	boost::shared_ptr<UIBase> dummy_blank_2(new UIDummy());
	dummy_blank_2->Resize(0, 20);

	std::vector<boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > > ui_list;
	ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, ui_identification);
	ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, dummy_blank_1);
	ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, ui_other);
	ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, dummy_blank_2);
	ui_list += boost::make_tuple(UIQueue::ROW_POSITION_TOP, ui_status);
	boost::shared_ptr<UIBase> result(new UIQueue(ui_list, UIQueue::INNER_POSITION_LEFT));
	return result;
}

const char* AlignmentToString(CharStatus::ALIGNMENT alignment) {
	switch(alignment) {
		case CharStatus::ALIGNMENT_GOOD:
			return "G";
		case CharStatus::ALIGNMENT_NEUTRAL:
			return "N";
		case CharStatus::ALIGNMENT_EVIL:
			return "E";
		default:
			BOOST_ASSERT(false);
	}
	return "ERROR";
}

} // anonymous

UICharStatus::UICharStatus(boost::shared_ptr<const std::string> frame_filename, boost::shared_ptr<const PTData> pt_data, unsigned int char_index) :
	UIBox(frame_filename), pt_data(pt_data), text_list(CreateTextList())
{
	BOOST_ASSERT(pt_data);
	BOOST_ASSERT(char_index < pt_data->GetCharacters().size());
	this->char_index = char_index;
	char_data = (*pt_data)[char_index];
	boost::optional<boost::shared_ptr<Error> > error = ReloadStatus();
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	error = SetInnerUI(CreateInnerUI(text_list));
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

UICharStatus::~UICharStatus() {
}

boost::optional<boost::shared_ptr<Error> > UICharStatus::ChangeChar(CHANGE_INDEX change_index) {
	const unsigned int size = pt_data->GetCharacters().size();
	if(char_index == 0 && change_index == CHANGE_INDEX_BACK) {
		char_index = size-1;
		return boost::none;
	}
	if(char_index == (size - 1) && change_index == CHANGE_INDEX_NEXT) {
		char_index = 0;
		return boost::none;
	}

	switch(change_index) {
		case CHANGE_INDEX_NEXT:
			char_index++;
			break;
		case CHANGE_INDEX_BACK:
			char_index--;
			break;
	}
	char_data = (*pt_data)[char_index];
	OPT_ERROR(ReloadStatus());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UICharStatus::ReloadStatus(void) {
	char text[256];
	text_list[STATUS_TEXT_NAME]->assign(*char_data->GetStatus()->GetName());
	text_list[STATUS_TEXT_LV]->assign(boost::lexical_cast<std::string>(char_data->GetStatus()->GetLv()));
	text_list[STATUS_TEXT_ALIGNMENT]->assign(AlignmentToString(char_data->GetStatus()->GetAlignment()));
	text_list[STATUS_TEXT_JOB]->assign(*char_data->GetStatus()->GetJob()->GetName());
	text_list[STATUS_TEXT_EXP]->assign(boost::lexical_cast<std::string>(char_data->GetStatus()->GetExp()));
	text_list[STATUS_TEXT_TG]->assign(boost::lexical_cast<std::string>(char_data->GetStatus()->GetTG()));
	text_list[STATUS_TEXT_AC]->assign(boost::lexical_cast<std::string>(char_data->GetAC()));
	sprintf(text, "%d/%d", char_data->GetHP(), char_data->GetStatus()->GetHP());
	text_list[STATUS_TEXT_HP]->assign(std::string(text));
	text_list[STATUS_TEXT_CONDITION]->assign(*char_data->GetCondition()->ToString());
	text_list[STATUS_TEXT_STR]->assign(boost::lexical_cast<std::string>(char_data->GetStr()));
	text_list[STATUS_TEXT_IQ]->assign(boost::lexical_cast<std::string>(char_data->GetIQ()));
	text_list[STATUS_TEXT_PIE]->assign(boost::lexical_cast<std::string>(char_data->GetPie()));
	text_list[STATUS_TEXT_VIT]->assign(boost::lexical_cast<std::string>(char_data->GetVit()));
	text_list[STATUS_TEXT_AGI]->assign(boost::lexical_cast<std::string>(char_data->GetAgi()));
	text_list[STATUS_TEXT_LUK]->assign(boost::lexical_cast<std::string>(char_data->GetLuk()));
	sprintf(text, "%d/%d/%d/%d/%d/%d/%d", char_data->GetMageMP()[0], char_data->GetMageMP()[1], char_data->GetMageMP()[2],
		char_data->GetMageMP()[3], char_data->GetMageMP()[4], char_data->GetMageMP()[5], char_data->GetMageMP()[6]);
	text_list[STATUS_TEXT_MAGE_MP]->assign(std::string(text));
	sprintf(text, "%d/%d/%d/%d/%d/%d/%d", char_data->GetPriestMP()[0], char_data->GetPriestMP()[1], char_data->GetPriestMP()[2],
		char_data->GetPriestMP()[3], char_data->GetPriestMP()[4], char_data->GetPriestMP()[5], char_data->GetPriestMP()[6]);
	text_list[STATUS_TEXT_PRIEST_MP]->assign(std::string(text));
	return boost::none;
}

} // uis

} // wten
