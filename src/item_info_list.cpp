#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace boost::assign;

namespace {

boost::shared_ptr<ItemInfoList> instance;

struct item_types_ : boost::spirit::qi::symbols<wchar_t, ItemInfo::ITEM_TYPE> {
	item_types_() {
		add
			(L"WEAPON",		ItemInfo::ITEM_TYPE_WEAPON)
			(L"SHIELD",		ItemInfo::ITEM_TYPE_SHIELD)
			(L"ARMOR",		ItemInfo::ITEM_TYPE_ARMOR)
			(L"HELMET",		ItemInfo::ITEM_TYPE_HELMET)
			(L"GAUNTLET",		ItemInfo::ITEM_TYPE_GAUNTLET)
			(L"ADORNMENT",	ItemInfo::ITEM_TYPE_ADORNMENT)
			(L"TOOL",		ItemInfo::ITEM_TYPE_TOOL)
		;
	}
} item_types_impl;

struct equip_jobs_ : boost::spirit::qi::symbols<wchar_t, boost::shared_ptr<const Job> > {
	equip_jobs_() {
		boost::shared_ptr<JobList> list = JobList::GetCurrentInstance();
		BOOST_FOREACH(boost::shared_ptr<const Job> job, list->GetList()) {
			add(job->GetIdentityName()->c_str(), job);
		}
	}
} equip_jobs_impl;

struct element_type_names_ : boost::spirit::qi::symbols<wchar_t, Action::ACTION_TYPE> {
	element_type_names_() {
		add
			(L"NORMAL",	Action::ACTION_TYPE_NORMAL)
			(L"FIRE",	Action::ACTION_TYPE_FIRE)
			(L"ICE",	Action::ACTION_TYPE_ICE)
			(L"POISON",	Action::ACTION_TYPE_POISON)
			(L"DRAIN",	Action::ACTION_TYPE_DRAIN)
			(L"STONE",	Action::ACTION_TYPE_STONE)
			(L"SPELL",	Action::ACTION_TYPE_SPELL)
			(L"SPECIAL",	Action::ACTION_TYPE_SPECIAL)
		;
	}
} element_type_names_impl;

boost::shared_ptr<const ItemInfo> CreateItemInfo(
	unsigned int id, boost::shared_ptr<const std::wstring> uncertainty_name, boost::shared_ptr<const std::wstring> name,
	boost::shared_ptr<const std::wstring> description, unsigned int sale_price, unsigned int price,
	ItemInfo::ITEM_TYPE item_type, unsigned int atk_base, unsigned int atk_count, unsigned int atk_bonus,
	unsigned int hit, unsigned int hit_count, int ac, unsigned int broken_probability,
	const std::vector<boost::shared_ptr<const Job> > &equip_possible, const std::vector<boost::tuple<Action::ACTION_TYPE, unsigned int> > &element_resist)
{
	std::vector<boost::tuple<EnemyInfo::MONSTER_TYPE, unsigned int> > monster_resist;
	std::vector<boost::tuple<CharCondition::CONDITION, unsigned int> > condition_resist;
	return boost::shared_ptr<const ItemInfo>(
		new ItemInfo(
			id, uncertainty_name, name,
			description, sale_price, price,
			item_type, atk_base, atk_count, atk_bonus,
			hit, hit_count, ac, broken_probability, equip_possible, element_resist, monster_resist, condition_resist)
	);
}

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
template <typename Iterator>
struct ItemInfoListCSVParser : ListCSVParserBase<Iterator, boost::shared_ptr<const ItemInfo> > {
	ItemInfoListCSVParser() {
		namespace qi = boost::spirit::qi;
		using qi::char_;
		using qi::uint_;
		using qi::int_;
		using qi::eol;

		quoted_item_types = '"' >> item_types_impl >> '"';
		item_types = quoted_item_types | item_types_impl;
		quoted_equip_jobs = '"' >> equip_jobs_impl >> '"';
		equip_jobs = quoted_equip_jobs | equip_jobs_impl;
		quoted_element_type_names = '"' >> element_type_names_impl >> '"';
		element_type_names = quoted_element_type_names | element_type_names_impl;
		element_types = (element_type_names >> ',' >> uint_)[qi::_val = boost::phoenix::bind(&boost::make_tuple<Action::ACTION_TYPE, unsigned int>, qi::_1, qi::_2)];
		data_line = (uint_ >> ',' >> string >> ',' >> string >> ','
			>> string >> ',' >> uint_ >> ',' >> uint_ >> ','
			>> item_types >> ',' >> uint_ >> ',' >> uint_ >> ',' >> uint_ >> ','
			>> uint_ >> ',' >> uint_ >> ',' >> int_ >> ',' >> uint_ >>
			*(',' >> equip_jobs) >> *(',' >> element_types) >> -eol)
			[qi::_val = boost::phoenix::bind(&CreateItemInfo, qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_6, qi::_7, qi::_8, qi::_9, qi::_10, qi::_11, qi::_12, qi::_13, qi::_14, qi::_15, qi::_16)];
		Initialize(data_line);
	}

	boost::spirit::qi::rule<Iterator, ItemInfo::ITEM_TYPE()> quoted_item_types;
	boost::spirit::qi::rule<Iterator, ItemInfo::ITEM_TYPE()> item_types;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const Job>()> quoted_equip_jobs;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const Job>()> equip_jobs;
	boost::spirit::qi::rule<Iterator, Action::ACTION_TYPE()> quoted_element_type_names;
	boost::spirit::qi::rule<Iterator, Action::ACTION_TYPE()> element_type_names;
	boost::spirit::qi::rule<Iterator, boost::tuple<Action::ACTION_TYPE, unsigned int>()> element_types;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const ItemInfo>()> data_line;
};
#pragma warning(pop)
#pragma pack(pop)

std::vector<boost::shared_ptr<const ItemInfo> > ReadItemInfo(const std::wstring &path) {
	typedef std::vector<wchar_t>::const_iterator Iterator;
	typedef ItemInfoListCSVParser<Iterator> Parser;
	std::vector<boost::shared_ptr<const ItemInfo> > result;

	std::vector<wchar_t> data;
	boost::optional<boost::shared_ptr<Error> > error = UTF8FileRead(path, &data);
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
		return result;
	}
	Iterator first = data.begin();
	const Iterator last = data.end();

	Parser rule;
	const bool parse_result = boost::spirit::qi::parse(first, last, rule, result);
	BOOST_ASSERT(parse_result);
	BOOST_ASSERT(first == last);
	return result;
}

} // anonymous

ItemInfoList::ItemInfoList(const std::vector<boost::shared_ptr<const ItemInfo> >& list) :
	list(list)
{
	BOOST_FOREACH(boost::shared_ptr<const ItemInfo> info, this->list) {
		BOOST_ASSERT(info);
	}
}

ItemInfoList::~ItemInfoList() {
}

//static
boost::shared_ptr<ItemInfoList> ItemInfoList::GetCurrentInstance(void) {
	if(!instance) {
		// TODO ��������
		const wchar_t *path = L"data/item/item_info_list.csv";
		std::vector<boost::shared_ptr<const ItemInfo> > list = ReadItemInfo(path);
		instance.reset(new ItemInfoList(list));
		BOOST_ASSERT(instance);
	}
	return instance;
}

std::vector<boost::shared_ptr<const ItemInfo> > ItemInfoList::GetList(void) const {
	return list;
}

std::vector<boost::shared_ptr<const ItemInfo> >::const_iterator ItemInfoList::Begin(void) const {
	return list.begin();
}

std::vector<boost::shared_ptr<const ItemInfo> >::const_iterator ItemInfoList::End(void) const {
	return list.end();
}

} // wten
